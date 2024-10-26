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

// bool execute_child(t_condition *condition, t_node *node, t_exec_info *info, int i)
// {
// 	if (i == 0)//first
// 	{
// 		wrap_dup2(info->fds[WRITE], STDOUT_FILENO);
// 		set_redirect_fd(node);
// 		wrap_close(info->fds[READ]);
// 		wrap_close(info->fds[WRITE]);
// 	}
// 	else if(i < info->pipe_count)//middle
// 	{
// 		wrap_dup2(info->keep_fd, STDIN_FILENO);
// 		wrap_dup2(info->fds[WRITE], STDOUT_FILENO);
// 		set_redirect_fd(node);
// 		wrap_close(info->keep_fd);
// 		wrap_close(info->fds[READ]);
// 		wrap_close(info->fds[WRITE]);
// 	}
// 	else//last
// 	{
// 		wrap_dup2(info->keep_fd, STDIN_FILENO);
// 		set_redirect_fd(node);
// 		wrap_close(info->keep_fd);
// 	}
// 	execute(condition, node);
// 	return (false);
// }

void init_exec_info(t_exec_info *info, t_node *node)
{
	ft_memset(info, 0, sizeof(t_exec_info));
	info->keep_fd = -2;
	info->pipe_count = count_pipe(node);
}

// bool execute_while_pipe(t_condition *condition, t_node *node)
// {
// 	// int fds[2];
// 	// int keep_fd = -2;
// 	int i = 0;
// 	t_exec_info info;
// 	pid_t pid;
	
// 	init_exec_info(&info, node);
// 	while (node)
// 	{
// 		if (node->kind == NODE_CMD)
// 		{
// 			if (i < info.pipe_count && pipe(info.fds) == -1)
// 			{
// 				put_error(strerror(errno));
// 				return (false);
// 			}
// 			pid = fork();
// 			if (pid == -1)
// 			{
// 				put_error(strerror(errno));
// 				return (false);
// 			}
// 			else if(!pid)
// 			{
// 				// execute_child(condition, node, &info, i);
// 				if (i == 0)//first
// 				{
// 					wrap_dup2(info.fds[WRITE], STDOUT_FILENO);
// 					set_redirect_fd(node);
// 					wrap_close(info.fds[READ]);
// 					wrap_close(info.fds[WRITE]);
// 				}
// 				else if(i < info.pipe_count)//middle
// 				{
// 					wrap_dup2(info.keep_fd, STDIN_FILENO);
// 					wrap_dup2(info.fds[WRITE], STDOUT_FILENO);
// 					set_redirect_fd(node);
// 					wrap_close(info.keep_fd);
// 					wrap_close(info.fds[READ]);
// 					wrap_close(info.fds[WRITE]);
// 				}
// 				else//last
// 				{
// 					wrap_dup2(info.keep_fd, STDIN_FILENO);
// 					set_redirect_fd(node);
// 					wrap_close(info.keep_fd);
// 				}
// 				execute(condition, node);
// 			}
// 			else
// 			{
// 				waitpid(pid, NULL, 0);
// 				if (i == 0)
// 				{
// 					wrap_close(info.fds[WRITE]);
// 					info.keep_fd = info.fds[READ];
// 				}
// 				else if (i < info.pipe_count)
// 				{
// 					wrap_close(info.keep_fd);
// 					wrap_close(info.fds[WRITE]);
// 					info.keep_fd = info.fds[READ];
// 				}
// 				else
// 				{
// 					wrap_close(info.keep_fd);
// 				}
// 				if (node->fd_in != -2)
// 				{
// 					wrap_close(node->fd_in);
// 					node->fd_in = -2;
// 				}
// 				if (node->fd_out != -2)
// 				{
// 					wrap_close(node->fd_out);
// 					node->fd_out = -2;
// 				}
// 			}
// 			i++;
// 		}
// 		node = node->next;
// 	}
// 	return (true);
// }

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

bool execute_loop(t_condition *condition, t_node *node)
{
	pid_t *pid;
	int pipe_count;
	int i;

	pipe_count = count_pipe(node);
	i = 0;
	pid = ft_calloc(pipe_count + 1, sizeof(pid_t));
	while(node)
	{
		if (node->kind == NODE_CMD)
		{
			pid[i] = fork();
			if(pid[i] == -1)
			{
				put_error(strerror(errno));
				return (false);
			}
			if (pid[i] == 0)
			{
				if (i == 0)
				{
					wrap_dup2(node->next->fds[WRITE], STDOUT_FILENO);
					set_redirect_fd(node);
					wrap_close(node->next->fds[READ]);
					wrap_close(node->next->fds[WRITE]);
				}
				else if(i < pipe_count)
				{
					wrap_dup2(node->prev->fds[READ], STDIN_FILENO);
					wrap_dup2(node->next->fds[WRITE], STDOUT_FILENO);
					wrap_close(node->prev->fds[READ]);
					wrap_close(node->prev->fds[WRITE]);
					wrap_close(node->next->fds[READ]);
					wrap_close(node->next->fds[WRITE]);
					set_redirect_fd(node);
				}
				else
				{
					wrap_dup2(node->prev->fds[READ], STDIN_FILENO);
					wrap_close(node->prev->fds[WRITE]);
					wrap_close(node->prev->fds[READ]);
					set_redirect_fd(node);
				}
				execute(condition, node);
			}
			else
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
			}
			i++;
		}
		node = node->next;
	}
	i = 0;
	while (i < pipe_count + 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
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
		// execute_while_pipe(condition, node);
		execute_loop(condition, node);
	}
	return (true);
}
