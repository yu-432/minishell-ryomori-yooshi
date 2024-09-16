/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:03:44 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:48:06 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sub_len;
	size_t	i;

	if (!s)
		return (NULL);
	else if (ft_strlen(s) <= start || len == 0)
		sub_len = 0;
	else if (ft_strlen(s) > start + len)
		sub_len = len;
	else
		sub_len = ft_strlen(s) - start;
	substr = (char *)malloc((sub_len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
