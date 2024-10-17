#include "../../header/token.h"
#include "../../header/lexer.h"
#include "../../libft/libft.h"

void update_quote_status(t_lexer *info, char c)
{
	if (info->quote == 0)
		info->quote = c;
	else if (info->quote == c)
		info->quote = 0;
}

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

bool expand_dollar(t_condition *condition, t_token *tokenized)
{
	int i;
	t_lexer info;

	i = 0;
	ft_memset(&info, 0, sizeof(t_lexer));
	while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]))
			update_quote_status(&info, tokenized->token[i]);
		if (tokenized->token[i] == '$' && info.quote != SINGLE_QUOTE)
		{
			if (!get_env_name(condition, tokenized, &info, &i))
				return (false);
		}
		else
			i++;
	}
	return (true);
}

bool expand_token(t_condition *condition, t_token *tokenized)
{
	while (tokenized)
	{
		if (tokenized->kind == TOKEN_WORD)
		{
			if (!expand_dollar(condition, tokenized))
				return (false);
			if (!expand_quote(tokenized))
				return (false);
		}
		tokenized = tokenized->next;
	}
	return (true);
}
