/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:37 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:54:38 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token.h"
#include "condition.h"
#include "standard.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_lexer
{
	char *env_key;
	char quote;
}	t_lexer;

bool is_space(char c);
bool is_metacharacter(char c);
bool is_quote(char c);
t_token *find_tail_token(t_token *token);
t_token *lexer(t_condition *condition, char *line);
t_token *tokenizer(char *line);
t_token *new_token(char *token, t_token_kind kind);
bool expand_token(t_condition *condition, t_token *tokenized);
bool find_syntax_error(t_condition *condition, t_token *tokenized);
void free_tokens(t_token *token);
int get_token_kind(char *token);
int count_same_char(char *line, char c);
bool expand_quote(t_token *tokenized);
bool expand_dollar(t_condition *condition, t_token *tokenized);
bool append_char(char **str, char c);
void update_quote_status(t_lexer *info, char c);
bool ft_strjoin_free(char **s1, char *s2);
char *find_env(t_condition *condition, char *env_key);
int count_envname_len(t_token *tokenized, int *i);




# endif