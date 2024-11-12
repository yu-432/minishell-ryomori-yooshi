#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

static void update_quote_status(t_lexer *info, char c)
{
	if (info->quote == 0)
		info->quote = c;
	else if (info->quote == c)
		info->quote = 0;
}

static bool ft_strjoin_free(char **s1, char *s2)
{
	char *new;

	if (!s1 || !s2)
		return (false);
	new = ft_strjoin(*s1, s2);
	if (!new)
		return (false);
	free(*s1);
	*s1 = new;
	return (true);
}

static char *find_env(t_condition *condition, char *env_key)
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

static bool replace_env(t_token *token, char *env_value, int env_len)
{
	char *new;
	int i;

	if (!env_value)
		env_value = "";
	i = 0;
	new = ft_strdup("");
	if (!new)
		return (false);
	while(token->token[i])
	{
		if (token->token[i] == '$')
		{
			if (!ft_strjoin_free(&new, env_value))
				return (false);
			i += env_len;
			if (!ft_strjoin_free(&new, token->token + i + 1))
				return (free(new), false);
			break ;
		}
		else
			if (!append_char(&new, token->token[i++]))
				return (free(new), false);
	}
	free(token->token);
	token->token = new;
	return (true);
}

static bool get_env_name(t_condition *condition, t_token *tokenized, t_lexer *info, int *i)
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
		return (false);
	if (info->env_key[0] == '\0')
	{
		(*i)++;
		return (true);
	}
	if (!replace_env(tokenized, find_env(condition, info->env_key), ft_strlen(info->env_key)))
		return (false);
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
