/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:39:47 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/15 10:40:03 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/signal.h"	
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include <sys/ioctl.h>

void	heredoc_handler(int signum)
{
	g_sig = signum;
}

void	handler(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = signum;
}
