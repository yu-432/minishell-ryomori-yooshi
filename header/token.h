#ifndef TOKEN_H
# define TOKEN_H

#include "stdbool.h"

typedef enum e_token_kind
{
	TOKEN_UNKNOWN,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_LPARENT,
	TOKEN_RPARENT,
}	t_token_kind;

typedef struct s_token_list
{
	t_token_kind	kind;
	char			*token;
	bool			has_dollar;
	t_token_list	*next;
}	t_token_list;

# endif