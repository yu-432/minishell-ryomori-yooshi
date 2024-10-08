#ifndef LEXER_H
# define LEXER_H

#include "token.h"
#include "condition.h"
#include "standard.h"

bool is_space(char c);
bool is_metacharacter(char c);
t_token *find_tail_token(t_token *token);
bool lexer(t_condition *condition, char *line);
t_token *tokenizer(char *line);
t_token *new_token(char *token, t_token_kind kind);




# endif