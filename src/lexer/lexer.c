#include "../../header/lexer.h"
#include "../../header/standard.h"



bool lexer(t_condition *condition, char *line)
{
	t_token *tokenized;
	int count = 1;

	tokenized = tokenizer(line);
	find_syntax_error(condition, tokenized);
	expand_token(condition, tokenized);

	while(tokenized)
	{
		printf("token[%u] kind = %u : %s\n", count, tokenized->kind, tokenized->token);
		count++;
		tokenized = tokenized->next;
	}
	(void)condition;
	return (true);
}