/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:41 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:56:43 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/print.h"


void put_redirect_error(t_condition *condition, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
	condition->exit_status = 1;
}

bool redirect_in(t_condition *condition, t_node *node, int i)
{
	int fd;

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

bool redirect_out(t_condition *condition, t_node *node, int i)
{
	int fd;

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
	if(node->fd_out != -2)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}

bool redirect_append(t_condition *condition, t_node *node, int i)
{
	int fd;

	reset_fd(&node->fd_out);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (put_redirect_error(condition, node->argv[i + 1]), false);
	if(node->fd_out != -2)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}