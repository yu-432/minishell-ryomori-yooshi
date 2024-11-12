/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:51 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:57:52 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

void put_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void put_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}
