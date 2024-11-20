/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:21 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 13:56:45 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtin_func.h"

long	over_256(long num)
{
	long	long_num_over;

	long_num_over = 0;
	while (num >= 256)
		num %= 256;
	long_num_over = num;
	return (long_num_over);
}

long	negative_num(long num)
{
	long	digit;
	long	result;

	digit = 0;
	result = 0;
	if (num == LONG_MIN)
		digit = (unsigned long)LONG_MIN % 256;
	else
		digit = (-num) % 256;
	if (digit != 0)
		result = 256 - digit;
	else
		result = 0;
	return (result);
}

long	exit_status_num(long num)
{
	long	result;

	if (num >= 256)
		return (result = over_256(num));
	else if (num < 0)
		return (result = negative_num(num));
	else
		return (num);
}

bool	is_check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (false);
	}
	return (true);
}
