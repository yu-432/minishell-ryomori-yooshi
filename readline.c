/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:29:30 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/18 18:02:28 by yooshima         ###   ########.fr       */
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
	t_token *token;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("test> ");
		if (line == NULL)
		{
			printf("Rreadline error\n");
			break ;
		}
		printf("input = %s\n", line);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
	printf("exit\n");
}