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
bool get_env_name(t_condition *condition, t_token *tokenized, t_lexer *info, int *i);
bool replace_env(t_token *token, char *env_value, int env_len);
char *find_env(t_condition *condition, char *env_key);
bool append_char(char **str, char c);
bool find_syntax_error(t_condition *condition, t_token *tokenized);
void free_tokens(t_token *token);
int get_token_kind(char *token);


# endif