/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:10:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/20 21:41:28 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "libft/libft.h"


typedef struct s_token	t_token;

typedef enum {
	TOKEN_WORD,//文字列
	TOKEN_OPE,//operator
	TOKEN_META,
	TOKEN_EOF,
}	t_token_kind;

struct	s_token	{
	char 			*token;
	t_token_kind	kind;
	t_token			*next;
}	;

struct s_cmd_tree {
	char *cmd;
	struct s_cmd_tree *first;
	struct s_cmd_tree *second;
};

int	main(int argc, char **argv, char **envp);
int	interpret(char *line, char **argv);
char	*find_command(char *line);
t_token *tokenize(char *line);


#endif
