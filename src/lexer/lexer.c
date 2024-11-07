#include "../../header/lexer.h"
#include "../../header/standard.h"



t_token *lexer(t_condition *condition, char *line)
{
	t_token *tokenized;

	tokenized = tokenizer(line);
	if (!tokenized)
		return (NULL);
	if (!find_syntax_error(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	if (!expand_token(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	(void)condition;
	return (tokenized);
}