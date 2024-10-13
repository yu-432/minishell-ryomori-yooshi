#include "../../header/lexer.h"
#include "../../header/standard.h"

bool lexer(t_condition *condition, char *line)
{
	t_token *tokenized;

	tokenized = tokenizer(line);
	expand_token(condition, tokenized);

	while(tokenized)
	{
		printf("token:%s ", tokenized->token);
		printf("kind:%d\n", tokenized->kind);
		tokenized = tokenized->next;
		printf("----------next----------\n");
	}
	(void)condition;
	return (true);
}