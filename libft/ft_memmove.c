/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:41:09 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:46:23 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = dest;
	str2 = (unsigned char *)src;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (dest > src)
		while (len--)
			str1[len] = str2[len];
	else
	{
		i = 0;
		while (i < len)
		{
			str1[i] = str2[i];
			i++;
		}
	}
	return (dest);
}
