#include "../../header/lexer.h"
#include "../../header/standard.h"

bool lexer(t_condition *condition, char *line)
{
	t_token *tokenized;

	tokenized = tokenizer(line);
	// expand_dollar(tokenized);
	while(tokenized)
	{
		printf("token:%s ", tokenized->token);
		printf("kind:%d ", tokenized->kind);
		tokenized = tokenized->next;
		printf("----------next----------\n");
	}
	(void)condition;
	return (true);
}