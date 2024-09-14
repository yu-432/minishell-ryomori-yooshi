/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:29:30 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/14 20:41:38 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// cc readline.c -lreadline -lhistory

//入力された文字をプリントする
//readlineの戻り値であるlineはmallocされているのでfreeする必要がある
//add_historyで履歴に追加する

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("test> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("input = %s\n", line);
		if (line)
			add_history(line);
		free(line);
	}
	printf("exit\n");
}