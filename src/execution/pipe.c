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

bool set_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_dup2(node->fd_in, STDIN_FILENO);
		wrap_close(node->fd_in);
	}
	if(node->fd_out != -2)
	{
		wrap_dup2(node->fd_out, STDOUT_FILENO);
		wrap_close(node->fd_out);
	}
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
	}
	if(pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	return (true);
}

void init_exec_info(t_exec_info *info, t_node *node)
{
	ft_memset(info, 0, sizeof(t_exec_info));
	info->keep_fd = -2;
	info->pipe_count = count_pipe(node);
}

bool make_pipe(t_node *node)
{
	while (node)
	{
		if (node->kind == NODE_PIPE)
		{
			if (pipe(node->fds) == -1)
			{
				put_error(strerror(errno));
				return (false);
			}
		}
		node = node->next;
	}
	return (true);
}

bool child_process(t_condition *condition, t_node *node, int i, int pipe_count)
{
	if (i > 0) //handle input fd
	{
		wrap_dup2(node->prev->fds[READ], STDIN_FILENO);
		wrap_close(node->prev->fds[READ]);
		wrap_close(node->prev->fds[WRITE]);
	}
	if (i < pipe_count) //handle output fd
	{
		wrap_dup2(node->next->fds[WRITE], STDOUT_FILENO);
		wrap_close(node->next->fds[READ]);
		wrap_close(node->next->fds[WRITE]);
	}
	set_redirect_fd(node);
	execute(condition, node);
	return (true);
}

bool parent_process(t_condition *condition, t_node *node)
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
	if(node->prev->kind == NODE_PIPE)
	{
		wrap_close(node->prev->fds[READ]);
		wrap_close(node->prev->fds[WRITE]);
	}
	(void)condition;
	return (true);
}

bool execute_loop(t_condition *condition, t_node *node)
{
	pid_t *pid;
	int pipe_count;
	int i;

	pipe_count = count_pipe(node);
	pid = ft_calloc(pipe_count, sizeof(pid_t));
	i = 0;
	while(node)
	{
		if (node->kind == NODE_CMD)
		{
			if((pid[i] = fork()) ==  -1)
				return (put_error(strerror(errno)), false);
			if (pid[i] == 0)
				child_process(condition, node, i, pipe_count);
			else
				parent_process(condition, node);
			i++;
		}
		node = node->next;
	}
	while (i >= 0)
		waitpid(pid[i--], NULL, 0);
	return (true);
}

bool exec_command(t_condition *condition, t_node *node)
{
	printf("-----result-----\n");
	if (!node->next)
		execute_single_command(condition, node);
	else
	{
		make_pipe(node);
		execute_loop(condition, node);
	}
	return (true);
}
