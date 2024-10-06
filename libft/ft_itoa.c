/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:04:26 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:41:59 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (1)
	{
		n /= 10;
		len++;
		if (n == 0)
			break ;
	}
	return (len);
}

static char	*set_nb(char *result, int n)
{
	int	len;

	len = nb_len(n);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	while (1)
	{
		result[len - 1] = n % 10 + '0';
		n /= 10;
		if (n == 0)
			break ;
		len--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;

	if (n == -2147483648)
	{
		result = (char *)malloc(12 * sizeof(char));
		if (!result)
			return (NULL);
		ft_strlcpy(result, "-2147483648", 12);
		return (result);
	}
	result = (char *)malloc(nb_len(n) + 1);
	if (!result)
		return (NULL);
	set_nb(result, n);
	return (result);
}
