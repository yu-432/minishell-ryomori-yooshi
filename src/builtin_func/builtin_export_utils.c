
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"
#include "../../header/builtin_func.h"
#include "../../header/print.h"

void	export_env(t_condition *condition)
{
	t_item	*current;

	current = condition->environ;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

bool	check_condition(t_condition *condition, char **argv)
{
	if (!*argv)
		return (export_env(condition), true);
	if (!ft_strchr(*argv, '='))
		return (true);
	return (false);
}
