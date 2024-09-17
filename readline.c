/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryomori <ryomori@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 03:08:15 by ryomori           #+#    #+#             */
/*   Updated: 2024-09-17 03:08:15 by ryomori          ###   #########include  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	// rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		printf("%s\n", line);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
	return (0);
}


// line -> 0x0asdjbu -> "abc"