#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execve.h"
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

bool is_not_redirect(char *str)
{
	int kind;

	kind = get_token_kind(str);
	if (kind == TOKEN_REDIRECT_IN || kind == TOKEN_REDIRECT_OUT ||\
		kind == TOKEN_REDIRECT_APPEND || kind == TOKEN_REDIRECT_HEREDOC)
		return (false);
	return (true);
}

int count_cmd_arg(t_node *node)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (node->argv[i])
	{
		if (is_not_redirect(node->argv[i]))
			count++;
		else
			count--;
		i++;
	}
	return (count);
}

char **molding_argv(t_node *node)
{
	char **res;
	int count;
	int i;
	int j;

	count = count_cmd_arg(node);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (is_not_redirect(node->argv[j]))
			res[i++] = node->argv[j];
		else
			j++;
		j++;
	}
	return (res);
}

char *take_env_value(t_condition *condition, char *key)
{
	t_item *current;

	current = condition->environ;
	while (current)
	{
		if (!ft_strncmp(current->key, key, strlen(key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*find_command_path(t_condition *condition, char *command)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	path = ft_split(take_env_value(condition, "PATH"), ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", command);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
			return (free(path), joined);
		free(joined);
		i++;
	}
	free(path);
	return (NULL);
}

bool execute(t_condition *condition, t_node *node)
{
	char **argv;
	char *path;

	argv = molding_argv(node);
	if (!argv)
		return (false);
	path = find_command_path(condition, argv[0]);
	if (!path)
	{
		put_error("command not found");
		return (false);
	}
	if (execve(path, argv, NULL) == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	free(argv);
	return (false);
}

bool is_pipe(char *str)
{
	if (!ft_strncmp(str, "|\0", 2))
		return (true);
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

bool execute_first_command(t_condition *condition, t_node *node, int *fds, int *keep_fd)
{
	pid_t pid;

	if (pipe(fds) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	if(pid == 0)
	{
		close(fds[READ]);
		dup2(fds[WRITE], STDOUT_FILENO);
		close(fds[WRITE]);
		if(node->fd_in != -2)
		{
			dup2(node->fd_in, STDIN_FILENO);
			close(node->fd_in);
		}
		execute(condition, node);
	}
	else
	{
		close(fds[WRITE]);
		waitpid(pid, NULL, 0);
		*keep_fd = fds[READ];
		printf("first keep fd %d\n", *keep_fd);
		close(fds[READ]);
	}
	return (true);
}

bool execute_last_command(t_condition *condition, t_node *node, int *keep_fd)
{
	pid_t pid;

	printf("hi!keep fd %d\n", *keep_fd);

	if (node->fd_out != -2)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	pid = fork();
	if (pid == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	if (pid == 0)
	{
		dup2(*keep_fd, STDIN_FILENO);
		close(*keep_fd);
		if (node->fd_out != -2)
		{
			dup2(node->fd_out, STDOUT_FILENO);
			close(node->fd_out);
		}
		execute(condition, node);
	}
	if(pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	return (true);
}


bool execute_while_command(t_condition *condition, t_node *node)
{
	int keep_fd;
	int fds[2];

	execute_first_command(condition, node, fds, &keep_fd);
	execute_last_command(condition, node, &keep_fd);
	return (true);
}

bool ryomori_pipe(t_condition *condition, t_node *node)
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
		ryomori_pipe(condition, node);
	return (true);
}
