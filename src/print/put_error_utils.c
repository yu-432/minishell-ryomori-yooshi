#include "../../libft/libft.h"
#include "../../header/condition.h"
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

