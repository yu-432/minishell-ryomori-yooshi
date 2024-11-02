#include "../../header/lexer.h"
#include "../../header/standard.h"



t_token *lexer(t_condition *condition, char *line)
{
	t_token *tokenized;
	// int count = 1;

	tokenized = tokenizer(line);
	if (!tokenized)
		return (NULL);
	if (!find_syntax_error(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	if (!expand_token(condition, tokenized))
		return (free_tokens(tokenized), NULL);

	t_token *temp = tokenized;
	// while(tokenized)
	// {
	// 	printf("token[%u] kind = %u : %s\n", count, tokenized->kind, tokenized->token);
	// 	count++;
	// 	tokenized = tokenized->next;
	// }
	tokenized = temp;	
	(void)condition;
	return (tokenized);
}