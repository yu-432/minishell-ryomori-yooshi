#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

int count_pipe(t_node *node)
{
	int count;

	count = 0;
	while (node)
	{
		if (get_token_kind(node->argv[0]) == TOKEN_PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

bool close_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_close(node->fd_in);
		node->fd_in = -2;
	}
	if (node->fd_out != -2)
	{
		wrap_close(node->fd_out);
		node->fd_out = -2;
	}
	return (true);
}

bool set_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
		wrap_dup2(node->fd_in, STDIN_FILENO);
	if(node->fd_out != -2)
		wrap_dup2(node->fd_out, STDOUT_FILENO);
	close_redirect_fd(node);
	return (false);
}

bool execute_single_command(t_condition *condition, t_node *node)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	if(pid == 0)
	{
		set_redirect_fd(node);
		execute(condition, node);//このままだと、エラー文も出力先が変更されているので修正する必要あり
	fprintf(stderr, "command not found\n");

	}
	if(pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	return (true);
}

bool init_exec_info(t_exec_info *info, t_node *node)
{
	ft_memset(info, 0, sizeof(t_exec_info));
	info->keep_fd = -2;
	info->pipe_count = count_pipe(node);
	return (true);
}

bool parent_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2])
{
	wrap_close(fds[WRITE]);
	if (info->keep_fd != -2)
		wrap_close(info->keep_fd);
	info->keep_fd = fds[READ];
	(void)condition;
	(void)node;
	(void)info;
	return (true);
}

bool child_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2])
{
	if (info->executed_count < info->pipe_count)
	{
		wrap_dup2(fds[WRITE], STDOUT_FILENO);
		wrap_close(fds[WRITE]);
		wrap_close(fds[READ]);
	}
	if (info->executed_count > 0)
	{
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
	}
	set_redirect_fd(node);
	execute(condition, node);
	fprintf(stderr, "command not found\n");
	exit(EXIT_FAILURE);
}

pid_t execute_last_command_wait(t_condition *condition, t_node *node, t_exec_info *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (put_error(strerror(errno)), false);
	if (pid == 0)
	{
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
		set_redirect_fd(node);
		execute(condition, node);
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		wrap_close(info->keep_fd);
		waitpid(pid, NULL, 0);
	}
	while(--info->executed_count >= 0)
		wait(NULL);
	return (0);
}

bool execute_loop(t_condition *condition, t_node *node)
{
	pid_t pid;
	t_exec_info info;
	int fds[2];

	if (!init_exec_info(&info, node))
		return (false);
	while(node->next)
	{
		if (node->kind == NODE_CMD)
		{
			pipe(fds);
			if((pid = fork()) ==  -1)
				return (put_error(strerror(errno)), false);
			if (pid == 0)
				child_process(condition, node, &info, fds);
			else
				parent_process(condition, node, &info, fds);
			close_redirect_fd(node);
			info.executed_count++;
		}
		node = node->next;
	}
	execute_last_command_wait(condition, node, &info);
	return (true);
}

bool exec_command(t_condition *condition, t_node *node)
{
	printf("-----result-----\n");
	if (node->next == NULL)
		execute_single_command(condition, node);
	else
		execute_loop(condition, node);
	return (true);
}

//出力先がpipeの場合、waitしない
//パイプで連結されたコマンドの場合、最後のコマンドのexit statusを返す