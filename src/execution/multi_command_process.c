/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:38 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:00:56 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

bool	parent_process(t_node *node, t_exec_info *info, int fds[2])
{
	wrap_close(fds[OUT]);
	if (info->keep_fd != INVALID_FD)
		wrap_close(info->keep_fd);
	info->keep_fd = fds[IN];
	close_redirect_fd(node);
	return (true);
}

bool	child_process(t_condition *condition, t_node *node, \
						t_exec_info *info, int fds[2])
{
	setup_child_signal();
	if (info->executed_count < info->pipe_count)
	{
		wrap_dup2(fds[OUT], STDOUT_FILENO);
		wrap_close(fds[OUT]);
		wrap_close(fds[IN]);
	}
	if (info->executed_count > 0)
	{
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
	}
	execute(condition, node);
	exit(EXIT_FAILURE);
}
