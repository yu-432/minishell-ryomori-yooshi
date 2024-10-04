/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:12:54 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:41:11 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	long_overflow(int sign, const char *str)
{
	long	temp;
	long	value;

	value = 0;
	while (ft_isdigit(*str))
	{
		temp = value * 10 + *str - '0';
		if (sign == 1 && !(temp >= value))
			return (LONG_MAX);
		else if (sign == -1 && !(temp >= value))
			return (LONG_MIN);
		value = temp;
		str++;
	}
	return (value);
}

int	ft_atoi(const char *str)
{
	long	value;
	int		sign;

	sign = 1;
	value = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	value = long_overflow(sign, str);
	return ((int)(value * sign));
}
