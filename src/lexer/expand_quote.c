#include "../../header/token.h"
#include "../../header/lexer.h"
#include "../../libft/libft.h"

bool expand_quote(t_token *tokenized)
{
	int i;
	char quote;
	char *new;

	i = 0;
	quote = 0;
	new = ft_strdup("");
	if (!new)
		return (false);
	while (tokenized->kind ==TOKEN_WORD && tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]) && quote == 0)
			quote = tokenized->token[i++];
		else if(tokenized->token[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			if (!append_char(&new, tokenized->token[i++]))
				return (false);
	}
	free(tokenized->token);
	tokenized->token = new;
	return (true);
}
