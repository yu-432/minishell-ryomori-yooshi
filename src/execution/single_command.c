/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:57 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:32:47 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"
#include "../../header/print.h"

static int	handle_single_builtin_command(t_condition *condition, t_node *node)
{
	int	keep_fds[3];

	storage_fd(keep_fds);
	if (!interpret_redirect(condition, node))
		return (false);
	set_redirect_fd(node);
	setup_parent_signal();
	execute_builtin(condition, node);
	restore_fd(keep_fds);
	return (EXIT_SUCCESS);
}

static void	wait_child_status(t_condition *condition, pid_t pid)
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
	if (!exec_heredoc(condition, node))
		return (false);
	if (is_builtin(node->argv[0]))
		return (handle_single_builtin_command(condition, node));
	pid = fork();
	if (pid == -1)
		return (put_error(strerror(errno)), false);
	if (!pid)
	{
		setup_child_signal();
		execute(condition, node);
		exit(EXIT_FAILURE);
	}
	wait_child_status(condition, pid);
	setup_parent_signal();
	return (EXIT_SUCCESS);
}
