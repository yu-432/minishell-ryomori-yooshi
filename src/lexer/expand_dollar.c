#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

void get_env_name(t_condition *condition, t_token *tokenized, t_lexer *info, int *i)
{
	int env_len;

	env_len = 0;
	(*i)++;
	if (tokenized->token[*i] == '?')
		env_len++;
	else
		while (ft_isalnum(tokenized->token[*i + env_len]))
			env_len++;
	info->env_key = ft_substr(tokenized->token, *i, env_len);
	if (!info->env_key)
	{
		printf("TODO:get_env_name malloc failed\n");
		exit(1);
	}
	if (info->env_key[0] == '\0')
	{
		(*i)++;
		return ;
	}
	replace_env(tokenized, find_env(condition, info->env_key), ft_strlen(info->env_key));
}

char *find_env(t_condition *condition, char *env_key)
{
	t_item *temp;

	temp = condition->environ;
	if (ft_strncmp(env_key, "?\0", 2) == 0)
		return (ft_itoa(condition->exit_status));
	while(temp)
	{
		if(ft_strncmp(temp->key, env_key, ft_strlen(temp->key) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	(void)condition;
	return (NULL);
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
			new = ft_strjoin(new, token->token + i);
			break ;
		}
		else
			append_char(&new, token->token[i++]);
	}
	free(token->token); 
	token->token = new;
}

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
