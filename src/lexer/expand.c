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

void expand_quote(t_token *tokenized)
{
	int i;
	char quote;
	char *new;

	i = 0;
	quote = 0;
	new = ft_strdup("");
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
			append_char(&new, tokenized->token[i++]);
	}
	free(tokenized->token);
	tokenized->token = new;
}

void expand_dollar(t_condition *condition, t_token *tokenized)
{
	int i;
	int env_len;
	t_lexer info;

	i = 0;
	env_len = 0;
	ft_memset(&info, 0, sizeof(t_lexer));
	while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]))
			update_quote_status(&info, tokenized->token[i]);
		if (tokenized->token[i] == '$' && info.quote != SINGLE_QUOTE)
			get_env_name(condition, tokenized, &info, &i);
		else
			i++;
	}
}

void expand_token(t_condition *condition, t_token *tokenized)
{
	int i;
	int env_len;

	i = 0;
	env_len = 0;
	while(tokenized)
	{
		if (tokenized->kind == TOKEN_WORD)
		{
			expand_dollar(condition, tokenized);
			expand_quote(tokenized);
		}
		tokenized = tokenized->next;
	}
}
