/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:54 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:56:56 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"
#include "../../header/print.h"

void set_exit_status_by_signal(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		g_sig = SIGQUIT;
	}
	if (WTERMSIG(status) == SIGINT)
		g_sig = SIGINT;
	write(STDERR_FILENO, "\n", 1);
}

void set_exit_status_by_status(t_condition *condition, int status)
{
	g_sig = 0;
	condition->exit_status = WEXITSTATUS(status);
}