/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:07 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 23:42:39 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

void	storage_fd(int *keep_fds)
{
	keep_fds[IN] = dup(STDIN_FILENO);
	keep_fds[OUT] = dup(STDOUT_FILENO);
	keep_fds[ERR] = dup(STDERR_FILENO);
}

bool	restore_fd(int *keep_fds)
{
	wrap_close(STDIN_FILENO);
	wrap_close(STDOUT_FILENO);
	wrap_close(STDERR_FILENO);
	wrap_dup2(keep_fds[IN], STDIN_FILENO);
	wrap_dup2(keep_fds[OUT], STDOUT_FILENO);
	wrap_dup2(keep_fds[ERR], STDERR_FILENO);
	wrap_close(keep_fds[IN]);
	wrap_close(keep_fds[OUT]);
	wrap_close(keep_fds[ERR]);
	return (true);
}

void close_prev_node_fd(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		close_redirect_fd(temp);
		temp = temp->next;
	}
}
