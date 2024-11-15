/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:13 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/15 12:03:20 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/signal.h"
#include "../../header/execution.h"
#include "../../header/print.h"

static void	heredoc_check_status(char *line, char *delimiter, \
									int read_status, int fd)
{
	if (g_sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		heredoc_free_exit(line, fd, 130);
	}
	if (read_status == INPUT_EOF)
	{
		put_heredoc_warning(delimiter);
		heredoc_free_exit(line, fd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		heredoc_free_exit(line, fd, EXIT_SUCCESS);
}

static void	heredoc_child_process(char *delimiter, int fds[2])
{
	char	*line;
	int		read_status;

	setup_heredoc_signal();
	wrap_close(fds[IN]);
	read_status = 0;
	line = NULL;
	while (true)
	{
		ft_putstr_fd(HEREDOC_PROMPT, STDERR_FILENO);
		line = get_line(STDIN_FILENO, &read_status);
		heredoc_check_status(line, delimiter, read_status, fds[OUT]);
		ft_putstr_fd(line, fds[OUT]);
		ft_putstr_fd("\n", fds[OUT]);
		free(line);
	}
}

static bool	heredoc_parent_process(t_condition *condition, t_node *node, \
									int fds[2], int pid)
{
	wait_child_status(condition, pid);
	setup_parent_signal();
	if (condition->exit_status)
	{
		wrap_double_close(fds[IN], fds[OUT]);
		return (false);
	}
	wrap_close(fds[OUT]);
	node->fd_in = fds[IN];
	(void)condition;
	return (true);
}

static bool	setup_heredoc(t_condition *condition, t_node *node, int i)
{
	int		fds[2];
	pid_t	pid;

	reset_fd(&node->fd_in);
	if (pipe(fds) == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	setup_ignore_signal();
	pid = fork();
	if (pid == -1)
	{
		wrap_double_close(fds[IN], fds[OUT]);
		return (put_error(strerror(errno)), false);
	}
	else if (!pid)
	{
		close_prev_node_fd(node);
		heredoc_child_process(node->argv[i + 1], fds);
	}
	if (!heredoc_parent_process(condition, node, fds, pid))
		return (false);
	return (true);
}

bool	exec_heredoc(t_condition *condition, t_node *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		if (is_pipe(node->argv[0]))
			break ;
		if (is_heredoc(node->argv[i]))
		{
			if (!node->argv[i + 1])
			{
				put_error("syntax error near unexpected token `newline'");
				return (false);
			}
			if (!setup_heredoc(condition, node, i))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}
