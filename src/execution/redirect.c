/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:41 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:02:25 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

bool	set_redirect(t_condition *condition, t_node *node, int i)
{
	t_token_kind	kind;

	kind = get_token_kind(node->argv[i]);
	if (kind == TOKEN_REDIRECT_IN)
		return (redirect_in(condition, node, i));
	else if (kind == TOKEN_REDIRECT_OUT)
		return (redirect_out(condition, node, i));
	else if (kind == TOKEN_REDIRECT_APPEND)
		return (redirect_append(condition, node, i));
	return (false);
}

bool	redirect_in(t_condition *condition, t_node *node, int i)
{
	int	fd;

	reset_fd(&node->fd_in);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_RDONLY);
	if (fd == -1)
		return (put_redirect_error(condition, node->argv[i + 1]), false);
	node->fd_in = fd;
	return (true);
}

bool	redirect_out(t_condition *condition, t_node *node, int i)
{
	int	fd;

	reset_fd(&node->fd_out);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		put_redirect_error(condition, node->argv[i + 1]);
		return (false);
	}
	if (node->fd_out != INVALID_FD)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}

bool	redirect_append(t_condition *condition, t_node *node, int i)
{
	int	fd;

	reset_fd(&node->fd_out);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (put_redirect_error(condition, node->argv[i + 1]), false);
	if (node->fd_out != INVALID_FD)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}
