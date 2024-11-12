/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:01 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:52:46 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

void	wrap_close(int fd)
{
	if (fd != -1 && close(fd) == -1)
	{
		perror("close");
		fprintf(stderr, "fd = %d\n", fd);
		exit(1);
	}
}

void	wrap_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(1);
	}
}
