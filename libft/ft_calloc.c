/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:21:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:41:33 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdint.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		ptr = (void *)malloc(1);
		if (!ptr)
			return (NULL);
	}
	else if (SIZE_MAX / size < count)
		return (NULL);
	else
	{
		ptr = (void *)malloc(count * size);
		if (ptr == NULL)
			return (NULL);
		ft_memset(ptr, 0, count * size);
	}
	return (ptr);
}
