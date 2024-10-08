#include "../../header/lexer.h"
#include "../../header/standard.h"

bool lexer(t_condition *condition, char *line)
{
	t_token *tokened;

	tokened = tokenizer(line);
	while(tokened)
	{
		printf("token:%s ", tokened->token);
		printf("kind:%d ", tokened->kind);
		printf("has_dollar:%d\n", tokened->has_dollar);
		tokened = tokened->next;
		printf("----------next----------\n");
	}
	(void)condition;
	return (true);
}