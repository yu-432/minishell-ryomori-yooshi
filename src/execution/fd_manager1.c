/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:04 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 23:44:15 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../header/execution.h"

void	reset_fd(int *fd)
{
	if (*fd != -2)
	{
		wrap_close(*fd);
		*fd = -2;
	}
}

void	close_child_process_fd(t_node *node)
{
	t_node *temp;

	temp = node;
	while (temp->prev)
		temp = temp->prev;
	while(temp)
	{
		close_redirect_fd(temp);
		temp = temp->next;
	}
}

bool	close_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_close(node->fd_in);
		node->fd_in = -2;
	}
	if (node->fd_out != -2)
	{
		wrap_close(node->fd_out);
		node->fd_out = -2;
	}
	return (true);
}

void	wrap_double_close(int fd1, int fd2)
{
	wrap_close(fd1);
	wrap_close(fd2);
}

bool	set_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_dup2(node->fd_in, STDIN_FILENO);
	}
	if (node->fd_out != -2)
	{
		wrap_dup2(node->fd_out, STDOUT_FILENO);
	}
	return (false);
}
