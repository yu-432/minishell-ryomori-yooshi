#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

bool set_redirect(t_condition *condition, t_node *node, int i)
{
	t_token_kind kind;
	bool is_success;

	is_success = true;
	kind = get_token_kind(node->argv[i]);
	if(kind == TOKEN_REDIRECT_IN)
		is_success = redirect_in(condition, node, i);
	else if(kind == TOKEN_REDIRECT_OUT)
		is_success = redirect_out(condition, node, i);
	else if(kind == TOKEN_REDIRECT_APPEND)
		is_success = redirect_append(condition, node, i);
	else if(kind == TOKEN_REDIRECT_HEREDOC)
		is_success = redirect_heredoc(condition, node, i);
	if(!is_success)
		return(false);
	return (true);
}

bool find_set_redirect(t_condition *condition, t_node *node)
{
	int i;

	i = 0;
	while(node->argv[i])
	{
		if (is_pipe(node->argv[0]))
			break;
		if (is_redirect(node->argv[i]))
		{
			if(!set_redirect(condition, node, i))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

bool interpret_redirect(t_condition *condition, t_node *node)
{
	char **new_argv;
	int i;

	i = 0;
	if(!find_set_redirect(condition, node))
		return (false);
	new_argv = molding_argv(node);
	if (!new_argv)
		return (false);
	free(node->argv);
	node->argv = new_argv;
	return (true);
}

void storage_fd(int *keep_fds)
{
	keep_fds[IN] = dup(STDIN_FILENO);
	keep_fds[OUT] = dup(STDOUT_FILENO);
	keep_fds[ERR] = dup(STDERR_FILENO);
}

bool restore_fd(int *keep_fds)
{
	wrap_close(STDIN_FILENO);
	wrap_close(STDOUT_FILENO);
	wrap_close(STDERR_FILENO);
	wrap_dup2(keep_fds[IN], STDIN_FILENO);
	wrap_dup2(keep_fds[OUT], STDOUT_FILENO);
	wrap_dup2(keep_fds[ERR], STDERR_FILENO);
	wrap_close(keep_fds[IN]);
	wrap_close(keep_fds[OUT]);
	wrap_close(keep_fds[ERR]);
	return (true);
}

int execute_single_command(t_condition *condition, t_node *node)
{
	pid_t pid;
	int status;
	int keep_fds[3];

	if (is_builtin(node->argv[0]))
	{
		storage_fd(keep_fds);
		set_redirect_fd(node);
		if(!interpret_redirect(condition, node))
			return (EXIT_FAILURE);
		execute_builtin(condition, node);
		restore_fd(keep_fds);
		return (EXIT_SUCCESS);
	}
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
