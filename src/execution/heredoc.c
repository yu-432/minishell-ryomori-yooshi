#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/signal.h"
#include "../../header/execution.h"

bool heredoc_strjoin(char **heredoc_str, char *line)
{
	char *temp;

	temp = ft_strjoin(*heredoc_str, line);
	if (!temp)
		return (false);
	free(*heredoc_str);
	*heredoc_str = NULL;
	*heredoc_str = ft_strjoin(temp, "\n");
	if (!heredoc_str)
		return (free(temp), false);
	return (true);
}

void put_heredoc_warning(int line_count, char *delimiter)
{
	char *line_count_str;

	line_count_str = ft_itoa(line_count);
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line_count, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

bool read_heredoc(t_node *node, int i)
{
	char *line;
	int line_count;

	line_count = 1;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (put_heredoc_warning(line_count, node->argv[i + 1]), true);
		if (!ft_strncmp(line, node->argv[i + 1], ft_strlen(node->argv[i + 1])))
		{
			free(line);
			break;
		}
		heredoc_strjoin(&node->heredoc_str, line);
		free(line);
		line_count++;
	}
	return (true);
}

void heredoc_child_process(t_node *node, int i, int fds[2])
{
	setup_child_signal();
	read_heredoc(node, i);
	dup2(fds[WRITE], STDOUT_FILENO);
	wrap_double_close(fds[READ], fds[WRITE]);
	ft_putstr_fd(node->heredoc_str, STDOUT_FILENO);
	exit(0);
}

bool heredoc_parent_process(t_node *node, int fds[2], int pid)
{
	int status;

	waitpid(pid, &status, 0);
	setup_parent_signal();
	close(fds[WRITE]);
	if (WTERMSIG(status) == SIGINT)
		return (write(STDERR_FILENO, "\n", 1), false);
	node->fd_in = fds[READ];
	return (true);
}

bool heredoc(t_node *node, int i)
{
	int fds[2];
	pid_t pid;

	if (pipe(fds) == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	setup_ignore_signal();
	pid = fork();
	if (pid == -1)
		return (put_error(strerror(errno)), false);
	else if (!pid)
		heredoc_child_process(node, i, fds);
	else
		if(!heredoc_parent_process(node, fds, pid))
			return (false);
	return (true);
}

bool redirect_heredoc(t_node *node, int i)
{
	reset_fd(&node->fd_in);
	free(node->heredoc_str);
	node->heredoc_str = ft_strdup("");
	if (!node->heredoc_str)
		return (false);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	if (!heredoc(node, i))
		return (false);
	return (true);
}
