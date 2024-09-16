/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:38:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:48:01 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_mach_head(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static int	char_mach_end(char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len--)
		if (s[len] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*value;

	if (!s1 || !set)
		return (NULL);
	while (char_mach_head((char *)set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (char_mach_end((char *)set, s1[len - 1]))
		len--;
	if (len < 0)
		len = 0;
	value = ft_substr(s1, 0, len);
	return (value);
}
