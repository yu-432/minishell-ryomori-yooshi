/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:13 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:56:14 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/signal.h"
#include "../../header/execution.h"
#include "../../header/print.h"

static void heredoc_child_process(char *delimiter, int fds[2])
{
	char *line;
	int line_count;

	setup_heredoc_signal();
	line_count = 0;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (put_heredoc_warning(line_count, delimiter));
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fds[OUT]);
		ft_putchar_fd('\n', fds[OUT]);
		free(line);
		line_count++;
	}
	wrap_double_close(fds[IN], fds[OUT]);
	exit(0);
}

static bool heredoc_parent_process(t_condition *condition, t_node *node, int fds[2], int pid)
{
	int status;

	waitpid(pid, &status, 0);
	close(fds[OUT]);
	node->fd_in = fds[IN];
	setup_parent_signal();
	if(WIFSIGNALED(status))
		return (set_exit_status_by_signal(status), false);
	(void)condition;
	return (true);
}

static bool heredoc(t_condition *condition, t_node *node, char *delimiter)
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
		heredoc_child_process(delimiter, fds);
	else
		if(!heredoc_parent_process(condition, node, fds, pid))
			return (false);
	return (true);
}

static bool redirect_heredoc(t_condition *condition, t_node *node, int i)
{
	reset_fd(&node->fd_in);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	if (!heredoc(condition, node, node->argv[i + 1]))
		return (false);
	(void)condition;
	return (true);
}

bool exec_heredoc(t_condition *condition, t_node *node)
{
	int i;

	i = 0;
	while(node->argv[i])
	{
		if (is_pipe(node->argv[0]))
			break;
		if (is_heredoc(node->argv[i]))
		{
			if(!redirect_heredoc(condition, node, i))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}
