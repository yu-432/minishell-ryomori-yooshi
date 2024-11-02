#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"

//=============================================================================
//==========================        ERROR        ===========================
//=============================================================================
void numeric_argument_error(char *argment)
{
	printf("exit: %s: numeric argument required\n", argment);
	exit(255);//bashの仕様に合わせると出力は2
}

void too_many_arguments_error(void)
{
	printf("exit: too many arguments\n");
	exit(1);
}

int tma_error_check(char **args)
{
	if(args[2] != NULL)
	{
		too_many_arguments_error();
		return (1);
	}
	return (0);
}
//=============================================================================
//==========================        SKIP_SPACE        ==========================
//=============================================================================

bool	is_spase(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *skip_space(char *str)
{
	while (is_spase(*str))
		str++;
	return (str);
}

//=============================================================================
//==========================        GET_SIGN        ============================
//=============================================================================
int get_sign_skip0(char *str)//long_over_checkで使用
{
	int sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	return (sign);
}

//=============================================================================
//==========================        OVER_256        ============================
//=============================================================================
long over_256(long num)
{
	long long_num_over;

	long_num_over = 0;
	while(num >= 256)
		num /= 256;
	long_num_over = num;
	return (long_num_over);
}

//=============================================================================
//==========================        EXIT_STATUS_NUM        =====================
//=============================================================================
long exit_status_num(long num)//builtin_exitで使用
{
	long result;

	if (num >= 256)
		return (result = over_256(num));
	else if (num < 0)
		return (result = negative_num(num));//作成していない
	else
		return (num);
}

//=============================================================================
//==========================        NEGATIVE_NUM        ========================
//=============================================================================
long negative_num(long num)//exit_status_numで使用
{
	long digit;
	long result;

	digit = 0;
	result = 0;
	if (num ==	LONG_MIN)
		digit = (unsigned long)LONG_MIN % 256;
	else
		digit = (-num) % 256;
	if(digit != 0)
		result = 256 - digit;
	else
		result = 0;
	return (result);
}

//=============================================================================
//==========================        BUILTIN_EXIT        =========================
//=============================================================================

bool is_check_num(char *str)//strが数字かどうかを判定(-.+)がある場合も考慮(一つだけ)
{
	int i;

	i = 0;
	if(str[i] == '-' || str[i] == '+')//exit -+-300などの場合errorにできる
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (false);
	}
	return (true);
}

//=============================================================================
//==========================        atolonglong        =========================
//=============================================================================

long atoll(const char *str)
{
	long long num;
	long long sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return ((long)num * sign);
}

//=============================================================================
//==========================        BUILTIN_EXIT        =========================
//=============================================================================

int	builtin_exit(char **args, t_condition *condition)
{
	char *argment;
	long num;
	long long_num_over;
	int judge;
	long result;

	result = 0;
	if(args[1] == NULL)
		exit(condition->exit_status);//execveの返り値を返す
	argment = (skip_space(args[1]));
	num = 0;
	if (!is_check_num(argment))
		numeric_argument_error(argment);
	else
	{
		if(tma_check(args))
			return (1);
		judge = long_over_check(argment);
		if (judge == 1)
			numeric_argument_error(argment);
		num = atoll(argment);
		result = exit_status_num(num);
			exit(result);
	}
	return (0);
}

//=============================================================================
//==========================        LONG_OVER_CHECK        =====================
//=============================================================================

int long_over_check(char *argment)
{
	const char *LONG_MAX_STR = "9223372036854775807";
	const char *LONG_MIN_STR = "-9223372036854775808";
	int i;
	
	int sign = 1;

	sign = get_sign_skip0(&argment);
	i = ft_strlen(argment);
	if (i > 19)
		return (1);
	if (i < 19)
		return (0);
	if (sign == 1)
	{
		if (ft_strncmp(argment, LONG_MAX_STR, 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(argment, LONG_MIN_STR, 19) > 0)
			return (1);
	}

}
