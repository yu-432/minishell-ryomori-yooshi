#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"

//=============================================================================
//==========================        ERROR        ===========================
//=============================================================================
void numeric_argument_error(char *argment)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argment, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(2);
}

int tma_error_check(t_condition *condition, char **args)
{
	if(args[2] != NULL)
	{
		put_error("exit: too many arguments");
		condition->exit_status = 1;
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
int get_sign_skip0(char **str)//long_over_checkで使用
{
	int sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '-' || **str == '+')
		str++;
	while (**str == '0')
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
		num %= 256;
	long_num_over = num;
	return (long_num_over);
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
	if (num == LONG_MIN)
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
//==========================        EXIT_STATUS_NUM        =====================
//=============================================================================
long exit_status_num(long num)//builtin_exitで使用
{
	long result;

	if (num >= 256)
		return (result = over_256(num));
	else if (num < 0)
		return (result = negative_num(num));
	else
		return (num);
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

long ft_atoll(const char *str)
{
	long num;
	long sign;

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
//==========================        LONG_OVER_CHECK        =====================
//=============================================================================//修正必要

int long_over_check(char *argment)
{
	const char *LONG_MAX_STR;
	const char *LONG_MIN_STR;
	int i;
	
	int sign = 1;
	i= 0;
	LONG_MAX_STR = "9223372036854775807";
	LONG_MIN_STR = "9223372036854775808";
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
	return (0);
}

//=============================================================================
//==========================        BUILTIN_EXIT        =========================
//=============================================================================

int	builtin_exit(t_condition *condition, char **args)
{
	char *argment;
	long num;
	int judge;
	long result;

	result = 0;
	if(args[1] == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(condition->exit_status);//execveの返り値を返す
	}
	argment = (skip_space(args[1]));
	num = 0;
	if (!is_check_num(argment))//strが数字かどうかを判定(-.+)がある場合も考慮(一つだけ)
		numeric_argument_error(argment);
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if(tma_error_check(condition, args))
			return (1);
		judge = long_over_check(argment);
		if (judge == 1)
			numeric_argument_error(argment);
		num = ft_atoll(argment);
		result = exit_status_num(num);
		exit(result);
	}
	return (0);
}
