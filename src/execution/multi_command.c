/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:21 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:36:34 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"
#include "../../header/print.h"

static void	wait_signal(t_condition *condition, t_exec_info *info)
{
	int	status;

	waitpid(info->pid[info->executed_count--], &status, 0);
	if (WIFSIGNALED(status))
		set_exit_status_by_signal(status);
	else if (WIFEXITED(status))
		set_exit_status_by_status(condition, status);
	while (info->executed_count >= 0)
	{
		waitpid(info->pid[info->executed_count], &status, 0);
		info->executed_count--;
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
	}
}

pid_t	execute_last_pipeline_cmd(t_condition *condition, t_node *node, \
									t_exec_info *info)
{
	if (!exec_heredoc(condition, node))
		return (false);
	setup_ignore_signal();
	info->pid[info->executed_count] = fork();
	if (info->pid[info->executed_count] == -1)
		return (put_error(strerror(errno)), false);
	if (!info->pid[info->executed_count])
	{
		setup_child_signal();
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
		if (!execute(condition, node))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	wrap_close(info->keep_fd);
	wait_signal(condition, info);
	setup_parent_signal();
	return (0);
}

bool	execute_pipeline_cmd(t_condition *condition, t_node *node, \
								t_exec_info *info)
{
	int	fds[2];

	pipe(fds);
	setup_ignore_signal();
	info->pid[info->executed_count] = fork();
	if (info->pid[info->executed_count] == -1)
		return (put_error(strerror(errno)), false);
	if (!info->pid[info->executed_count])
		child_process(condition, node, info, fds);
	parent_process(condition, node, info, fds);
	close_redirect_fd(node);
	info->executed_count++;
	return (true);
}