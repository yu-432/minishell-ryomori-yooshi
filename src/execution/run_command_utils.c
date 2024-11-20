/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:45 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 14:00:53 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

bool	is_redirect(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0 || \
		ft_strncmp(str, ">", 2) == 0 || \
		ft_strncmp(str, ">>", 3) == 0)
		return (true);
	return (false);
}

bool	is_heredoc(char *str)
{
	if (ft_strncmp(str, "<<", 3) == 0)
		return (true);
	return (false);
}
