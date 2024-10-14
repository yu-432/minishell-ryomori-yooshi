#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../header/condition.h"


void check_quote_error(char *token)
{
	int i;
	char quote;

	i = 0;
	while (token[i])
	{
		if (is_quote(token[i]))
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				i++;
			if (token[i] != quote)
			{
				printf("TODO:find_syntax_error quote error\n");
				exit(1);
			}
			i++;
		}
		else
			i++;
	}
}

void check_token_kind(t_token_kind kind)
{
	if (!(kind == TOKEN_WORD \
		|| kind == TOKEN_PIPE \
		|| kind == TOKEN_REDIRECT_IN \
		|| kind == TOKEN_REDIRECT_OUT \
		|| kind == TOKEN_REDIRECT_APPEND \
		|| kind == TOKEN_REDIRECT_HEREDOC \
		|| kind == TOKEN_EOF))
		{
			printf("TODO:find_syntax_error unknown token kind\n");
			exit(1);
		}
}

void find_syntax_error(t_condition *condition, t_token *tokenized)
{
	while (tokenized)
	{
		check_token_kind(tokenized->kind);
		check_quote_error(tokenized->token);

		tokenized = tokenized->next;
	}

	(void)condition;
}