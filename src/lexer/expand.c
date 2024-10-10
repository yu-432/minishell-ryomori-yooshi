#include "../../header/token.h"
#include "../../header/lexer.h"
#include "../../libft/libft.h"

void append_char(char **str, char c)
{
	char *new;
	char join[2];

	join[0] = c;
	join[1] = '\0';
	new = ft_strjoin(*str, join);
	if(!new)
	{
		printf("TODO:append_char malloc failed\n");
		exit(1);
	}
	free(*str);
	*str = new;
}

void replace_env(t_token *token, char *env_value, int env_len)
{
	char *new;
	int i;

	if (!env_value)
		env_value = "";//環境変数が存在しない場合要確認
	i = 0;
	new = ft_strdup("");
	while(token->token[i])
	{
		if (token->token[i] == '$')
		{
			new = ft_strjoin(new, env_value);
			i += env_len + 1;
		}
		else
			append_char(&new, token->token[i++]);
	}
	free(token->token); 
	token->token = new;
}
	
char *find_env(t_condition *condition, char *env_key)
{
	t_item *temp;

	temp = condition->environ;
	while(temp)
	{
		if(ft_strncmp(temp->key, env_key, ft_strlen(temp->key) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	(void)condition;
;	return (NULL);
}

void expand_dollar(t_condition *condition, t_token *tokenized)
{
	int i;
	int env_len;
	char *env_key;
	char quote;

	i = 0;
	env_len = 0;
	quote = 0;
	while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]) && quote == 0)
			quote = tokenized->token[i];
		else if (tokenized->token[i] == quote)
			quote = 0;
		if (tokenized->token[i] == '$' && quote != SINGLE_QUOTE)
		{
			i++;
			while (ft_isalnum(tokenized->token[i + env_len]))
				env_len++;
			env_key = ft_substr(tokenized->token, i , env_len);
			if(!env_key)
			{
				printf("TODO:expand_dollar malloc failed\n");
				exit(1);
			}
			replace_env(tokenized, find_env(condition, env_key), ft_strlen(env_key));
		}
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
			// expand_quote(tokenized);
		}
		tokenized = tokenized->next;
	}
}