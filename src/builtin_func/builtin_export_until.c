#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"
#include "../../header/builtin_func.h"

bool	is_envname(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	put_export_error(t_condition *condition, char *argv)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	condition->exit_status = 1;
}
