/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:37:07 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:47:53 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	if (i < len)
	{
		while (haystack[i])
		{
			j = 0;
			while (i + j < len && haystack[i + j] == needle[j] && needle[j])
				j++;
			if (j == ft_strlen(needle))
				return ((char *)haystack + i);
			i++;
		}
	}
	return (NULL);
}
