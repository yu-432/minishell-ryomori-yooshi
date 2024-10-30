#include "../../header/standard.h"
#include "../../libft/libft.h"

void builtin_echo(char **argv)
{
	int i;
	bool is_newline;

	i = 1;
	is_newline = true;
	if (!ft_strncmp(argv[1], "-n\0", 3))
	{
		is_newline = false;
		i++;
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
}