/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:44 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 01:21:20 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>

extern sig_atomic_t	g_sig;

void	setup_parent_signal(void);
void	setup_child_signal(void);
void	default_sig(int signum);
void	ignore_sig(int signum);
void	handle_sigint(int signum);
void	setup_ignore_signal(void);
void	child_signal_handler(int signum);
void	setup_heredoc_signal(void);

#endif