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

bool read_heredoc(t_node *node, int i)
{
	char *line;

	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (false);
		if (!ft_strncmp(line, node->argv[i + 1], ft_strlen(node->argv[i + 1])))
		{
			free(line);
			break;
		}
		heredoc_strjoin(&node->heredoc_str, line);
		free(line);
	}
	return (true);
}

bool heredoc(t_node *node, int i)//heredoc子プロセスを作成して、そこでheredocを読み込む
{
	int fds[2];
	pid_t pid;

	if (pipe(fds) == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	pid = fork();
	if (!pid)
	{
		setup_child_signal();
		read_heredoc(node, i);
		close(fds[READ]);
		dup2(fds[WRITE], STDOUT_FILENO);
		close(fds[WRITE]);
		ft_putstr_fd(node->heredoc_str, STDOUT_FILENO);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fds[WRITE]);
		node->fd_in = fds[READ];
	}
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
	heredoc(node, i);
	return (true);
}
