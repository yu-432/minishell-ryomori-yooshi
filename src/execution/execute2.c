#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"

bool is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "echo", 5) == 0 || \
		ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "pwd", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 6) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0 || \
		ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

void execute_builtin(t_condition *condition, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		builtin_echo(argv);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		builtin_cd(condition, argv);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		builtin_export(condition, argv);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		builtin_unset(condition, argv);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		builtin_env(condition);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		builtin_exit(condition, argv);
}