#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

int execute_single_command(t_condition *condition, t_node *node)
{
	pid_t pid;
	int status;

	if (is_builtin(node->argv[0]))
		return (execute_builtin(condition, node), 1);//////
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
	waitpid(pid, &status, 0);
	if(WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig = SIGINT;
	}
	if(WIFEXITED(status))
		condition->exit_status = WEXITSTATUS(status);
	setup_parent_signal();
	return (EXIT_SUCCESS);
}

void wait_signal(t_condition *condition, t_exec_info *info)
{
	int status;

	waitpid(info->pid[info->executed_count--], &status, 0);
	condition->exit_status = WEXITSTATUS(status);
	g_sig = WTERMSIG(status);
	while(info->executed_count >= 0)
	{
		waitpid(info->pid[info->executed_count], &status, 0);
		info->executed_count--;
	}
	if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
	}
}

pid_t execute_last_pipeline_cmd(t_condition *condition, t_node *node, t_exec_info *info)
{
	setup_ignore_signal();
	info->pid[info->executed_count] = fork();
	if (info->pid[info->executed_count] == -1)
		return (put_error(strerror(errno)), false);
	if (info->pid[info->executed_count] == 0)
	{
		setup_child_signal();
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
		if(!execute(condition, node))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	wrap_close(info->keep_fd);
	wait_signal(condition, info);
	setup_parent_signal();
	return (0);
}

bool execute_pipeline_cmd(t_condition *condition, t_node *node, t_exec_info *info)
{
	int fds[2];

	pipe(fds);
	setup_ignore_signal();
	if((info->pid[info->executed_count] = fork()) ==  -1)
		return (put_error(strerror(errno)), false);
	if (info->pid[info->executed_count] == 0)
		child_process(condition, node, info, fds);
	parent_process(condition, node, info, fds);
	close_redirect_fd(node);
	info->executed_count++;
	return (true);
}
