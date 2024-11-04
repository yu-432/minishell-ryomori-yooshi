#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"

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
		fprintf(stderr, "builtin command\n");
		execute_builtin(condition, node);
		return (true);
	}
	path = find_command_path(condition, node->argv[0]);
	if (!path)
	{
		put_error("command not found");
		exit (127);
	}
	execve(path, node->argv, NULL);
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
