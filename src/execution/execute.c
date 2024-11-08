#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"
#include "../../header/signal.h"

void execute_builtin(t_condition *condition, t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		builtin_echo(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		builtin_export(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		builtin_unset(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		builtin_env(condition);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		builtin_cd(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		builtin_pwd(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		builtin_exit(condition, node->argv);
	else
		fprintf(stderr, "error: builtin command not found\n");
}

int execute(t_condition *condition, t_node *node)
{
	char *path;

	set_redirect_fd(node);
	if (is_builtin(node->argv[0]))
	{
		execute_builtin(condition, node);
		return (EXIT_SUCCESS);
	}
	path = find_command_path(condition, node->argv[0]);
	if (!path)
	{
		ft_putstr_fd(node->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
	execve(path, node->argv, NULL);
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
