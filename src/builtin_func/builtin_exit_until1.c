#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/builtin_func.h"
#include "../../header/print.h"


void	numeric_argument_error(char *argment)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argment, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(2);
}

int	tma_error_check(t_condition *condition, char **args)
{
	if (args[2] != NULL)
	{
		put_error("exit: too many arguments");
		condition->exit_status = 1;
		return (1);
	}
	return (0);
}

bool	is_spase(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*skip_space(char *str)
{
	while (is_spase(*str))
		str++;
	return (str);
}

int	get_sign_skip0(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '-' || **str == '+')
		str++;
	while (**str == '0')
		str++;
	return (sign);
}
