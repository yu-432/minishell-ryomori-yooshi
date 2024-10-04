/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:57:32 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/02 13:53:35 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 - *str2 != 0)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

//#include <string.h>
//
// int main(void)
// {
// 	// char s1[] = "abcd";
// 	// char s2[] = "\200";
// 	long long i1[] = { 1, 2, 3, 4};
// 	long long i2[] = { 1, 2, 3000033333300000000, 4};
// 	size_t len = sizeof(i1);
// 	printf("%d\n", memcmp(i1, i2, len));
// 	printf("%d\n", ft_memcmp(i1, i2, len));

// }