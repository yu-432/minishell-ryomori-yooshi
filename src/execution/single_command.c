#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

static int handle_single_builtin_command(t_condition *condition, t_node *node, int keep_fds[3])
{
	storage_fd(keep_fds);
	set_redirect_fd(node);
	if(!interpret_redirect(condition, node))
		return (EXIT_FAILURE);
	execute_builtin(condition, node);
	restore_fd(keep_fds);
	return (EXIT_SUCCESS);
}

static void wait_child_status(t_condition *condition, pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if(WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig = SIGINT;
	}
	if(WIFEXITED(status))
		condition->exit_status = WEXITSTATUS(status);
}

int execute_single_command(t_condition *condition, t_node *node)
{
	pid_t pid;
	int keep_fds[3];

	if (is_builtin(node->argv[0]))
		return (handle_single_builtin_command(condition, node, keep_fds));
	setup_ignore_signal();
	pid = fork();
	if (pid == -1)
		return (put_error(strerror(errno)), false);
	if(pid == 0)
	{
		setup_child_signal();
		execute(condition, node);
		exit(EXIT_FAILURE);
	}
	wait_child_status(condition, pid);
	setup_parent_signal();
	return (EXIT_SUCCESS);
}