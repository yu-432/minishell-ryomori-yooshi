/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:10:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/29 13:12:58 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

//quoteの除去　環境変数の展開　閉じられていない引用符のエラー処理

bool	is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

bool	append_char(char **new_token, char c)
{
	char *temp;
	char join[2];

	join[0] = c;
	join[1] = '\0';
	temp = ft_strjoin(*new_token, join);
	if (!temp)
	{
		printf("expantion strjoin error\n");
		return (false);
	}
	free(*new_token);
	*new_token = temp;
	return (true);
}


char	*expand_quote(char **token)
{
	char	*new_token;
	char 	quote;

	new_token = ft_strdup("");
	while((**token))
	{
		if(is_quote(**token))
		{
			quote = (**token);
			(*token)++;
			while((**token) != quote)
			{
				if (!(**token))
				{
					printf("quote error\n");
					return (NULL);
				}
				else
					append_char(&new_token, **token);
				(*token)++;
			}
		}
		else
			append_char(&new_token, (**token));
		(*token)++;
	}
	return (new_token);
}

char	*expand_doller(char **token, int i)
{
	char *env_str;
	char *env_value;
	char *temp;
	int len;


	len = 0;
	while((*token)[i + len] && ft_isalnum((*token)[i + len]))
		len++;
	env_str = ft_substr(*token, i, len);
	printf("env_Str = %s, i %d, len %d\n", env_str, i, len);
	env_value = getenv(env_str);
	if (!env_value)
		return(printf("getenv error\n"), NULL);
	temp = ft_substr(*token, 0, i);
	while ((*token)[i] && ft_isalnum((*token)[i]))
		i++;
	temp = ft_strjoin(temp, env_value);
	while ((*token)[i])
	{
		temp = ft_strjoin(temp, &(*token)[i]);
		i++;
	}
	return (temp);
}

char	*check_doller(char **token)
{
	int i;
	char quote;
	char *new_token;
	char *temp;

	i = 0;
	quote = 0;
	while((*token)[i])
	{
		if(is_quote((*token)[i]))
		{
			if (quote == 0)
				quote = (*token)[i];
			else if (quote == (*token)[i])
				quote = 0;
		}
		if ((*token)[i] == '$' && quote != SINGLE_QUOTE)
		{
			new_token = expand_doller(token, ++i);
			if (!new_token)
				return ("strjoin error\n");
			temp = ft_substr(*token, 0, i - 1);
			ft_strjoin(temp, new_token);
			free(*token);
			free(temp);
			*token = new_token;
		}
		i++;
	}
	return (new_token);
}

int expantion_token(t_token *token)
{
	int i;
	char *temp;

	i = 0;
	while (token->kind != TOKEN_EOF)
	{
		check_doller(&token->token);
		temp = expand_quote(&token->token);
		if (!temp)
			return (1);
		token->token = temp;
		token = token->next;
	}
	return (0);
}