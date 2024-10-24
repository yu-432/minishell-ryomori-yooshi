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
		if (node->fd_in != -2)
		{
			dup2(node->fd_in, STDIN_FILENO);
			close(node->fd_in);
		}
		if (node->fd_out != -2)
		{
			dup2(node->fd_out, STDOUT_FILENO);
			close(node->fd_out);
		}
		execute(condition, node);//このままだと、エラー文も出力先が変更されているので修正する必要あり
	}
	if(pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	return (true);
}

bool execute_while_pipe(t_condition *condition, t_node *node)
{
	int fds[2];
	int keep_fd = -2;
	int i = 0;
	pid_t pid;
	
	int pipe_count = count_pipe(node);
	while (node)
	{
		if (node->kind == NODE_CMD)
		{
			if (i < pipe_count && pipe(fds) == -1)
			{
				put_error(strerror(errno));
				return (false);
			}
			pid = fork();
			if (pid == -1)
			{
				put_error(strerror(errno));
				return (false);
			}
			else if(!pid)
			{
				if (i == 0)//first
				{
					if(node->fd_in != -2)
					{
						dup2(node->fd_in, STDIN_FILENO);
						close(node->fd_in);
					}
					close(fds[READ]);
					dup2(fds[WRITE], STDOUT_FILENO);
					close(fds[WRITE]);
				}
				else if(i < pipe_count)//middle
				{
					dup2(keep_fd, STDIN_FILENO);
					close(keep_fd);
					close(fds[READ]);
					dup2(fds[WRITE], STDOUT_FILENO);
					close(fds[WRITE]);
				}
				else//last
				{
					if(node->fd_out != -2)
					{
						dup2(node->fd_out, STDOUT_FILENO);
						close(node->fd_out);
					}
					dup2(keep_fd, STDIN_FILENO);
					close(keep_fd);
				}
				execute(condition, node);
			}
			else
			{
				waitpid(pid, NULL, 0);
				if (i == 0)
				{
					close(fds[WRITE]);
					keep_fd = fds[READ];
				}
				else if (i < pipe_count)
				{
					close(keep_fd);
					close(fds[WRITE]);
					keep_fd = fds[READ];
				}
				else
				{
					close(keep_fd);
				}
				if (node->fd_in != -2)
				{
					close(node->fd_in);
					node->fd_in = -2;
				}
				if (node->fd_out != -2)
				{
					close(node->fd_out);
					node->fd_out = -2;
				}
			}
			i++;
		}
		node = node->next;
	}
	return (true);
}

bool exec_command_pipe(t_condition *condition, t_node *node)
{

	printf("-----result-----\n");
	if (!node->next)
		execute_single_command(condition, node);
	else
		execute_while_pipe(condition, node);
	return (true);
}
