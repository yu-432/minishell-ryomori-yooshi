/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:57 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:02:52 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

static int	handle_single_builtin_command(t_condition *condition, t_node *node)
{
	int		keep_fds[3];
	bool	is_fd_changed;

	is_fd_changed = false;
	if (!interpret_redirect(condition, node))
		return (false);
	if (node->fd_in != INVALID_FD || node->fd_out != INVALID_FD)
	{
		storage_fd(keep_fds);
		is_fd_changed = true;
	}
	set_redirect_fd(node);
	setup_parent_signal();
	execute_builtin(condition, node);
	if (is_fd_changed)
		restore_fd(keep_fds);
	return (EXIT_SUCCESS);
}

void	wait_child_status(t_condition *condition, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (!condition->exit_status)
	{
		if (WIFSIGNALED(status))
			set_exit_status_by_signal(status);
		else if (WIFEXITED(status))
			set_exit_status_by_status(condition, status);
	}
}

int	execute_single_command(t_condition *condition, t_node *node)
{
	pid_t	pid;

	setup_ignore_signal();
	if (is_builtin(node->argv[0]))
		return (handle_single_builtin_command(condition, node));
	pid = fork();
	if (pid == -1)
		return (put_error(strerror(errno)), false);
	if (!pid)
	{
		setup_child_signal();
		execute(condition, node);
	}
	wait_child_status(condition, pid);
	setup_parent_signal();
	close_redirect_fd(node);
	return (EXIT_SUCCESS);
}
