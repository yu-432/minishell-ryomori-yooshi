#include "../../header/token.h"
#include "../../header/lexer.h"
#include "../../libft/libft.h"

void expand_dollar(t_token *tokenized)
{
	int i;
	int env_len;
	char *env_value;

	i = 0;
	env_len = 0;
	while(tokenized)
	{
		while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
		{
			if (tokenized->token[i] == '$')
			{
				i++;
				while (ft_isalnum(tokenized->token[i]))
					env_len++;
				env_value = ft_substr(tokenized->token, i , env_len);
				if(!env_value)
				{
					
				}
			}
		}
	}
}