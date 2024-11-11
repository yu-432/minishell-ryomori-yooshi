#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../libft/libft.h"

void 	builtin_echo(t_condition *condition, char **argv)
{
	int		i;
	int		j;
	bool	is_newline;

	i = 1;
	is_newline = true;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
	{
		j = 2;
		while (argv[1][j] == 'n')
			j++;
		if (argv[1][j] == '\0')
		{
			is_newline = false;
			i++;
		}
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (is_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	(void)condition;
}