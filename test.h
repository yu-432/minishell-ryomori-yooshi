/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:10:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/25 17:07:46 by yooshima         ###   ########.fr       */
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
typedef struct s_node	t_node;

typedef enum {
	TOKEN_WORD,//文字列
	TOKEN_OPE,//operator
	TOKEN_META,//メタ文字
	TOKEN_EOF, //終端
}	t_token_kind;

typedef enum {
	NODE_CMD,
	NODE_OPE
}	t_node_kind;

struct	s_token	{
	char 			*token;
	t_token_kind	kind;
	t_token			*next;
}	;

struct s_node {
	t_token			*args;
	t_node_kind		kind;
	t_node			*next;
}	;

int	main(int argc, char **argv, char **envp);
int	interpret(char *line, char **argv);
char	*find_command(char *line);
t_token *tokenize(char *line);
t_token	*new_token(char *word, t_token_kind kind);
t_node	*parser(t_token *token);


#endif
