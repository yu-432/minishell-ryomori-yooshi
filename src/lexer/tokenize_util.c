#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/token.h"

bool is_space(char c)
{
	return(c == ' ' || c == '\t' || c == '\n');
}

bool is_metacharacter(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' \
			|| c == '<' || c =='>' || c == ' ' || c == '\t' || c == '\n');
}

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

t_token *find_tail_token(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_token *new_token(char *token, t_token_kind kind)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->kind = kind;
	return (new);
}