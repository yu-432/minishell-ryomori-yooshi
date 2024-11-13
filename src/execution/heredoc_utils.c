/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:13 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 10:21:22 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/signal.h"
#include "../../header/execution.h"
#include "../../header/print.h"
#include "../../header/lexer.h"

char	*get_line(int fd)
{
	char	buf;
	char	*result;

	result = ft_strdup("");
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			break ;
		ft_strjoin_free(&result, &buf);
	}
	return (result);
}
