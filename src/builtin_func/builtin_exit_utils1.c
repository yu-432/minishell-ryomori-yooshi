/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_until1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:55:18 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/builtin_func.h"
#include "../../header/print.h"


bool	is_spase(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*skip_space(char *str)
{
	while (is_spase(*str))
		str++;
	return (str);
}

int	get_sign_skip0(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '-' || **str == '+')
		str++;
	while (**str == '0')
		str++;
	return (sign);
}
