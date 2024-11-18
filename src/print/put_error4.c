/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:39:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/18 12:08:24 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/print.h"

int	filename_required_error(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": filename required\n", STDERR_FILENO);
	return (2);
}
