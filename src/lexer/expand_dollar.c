/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:19 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 14:09:05 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

static int	count_envname_len(char *token, int i)
{
	int	len;

	len = 0;
	if (token[i] == '?')
		len++;
	else
		while (ft_isalnum(token[i + len]) || token[i + len] == '_')
			len++;
	return (len);
}

static char	*split_keyname(char *token, int i)
{
	int	len;

	len = count_envname_len(token, i);
	return (ft_substr(token, i, len));
}

static bool	handle_dollar(t_condition *condition, t_token *tokenized, \
							char **new, int *i)
{
	char	*env_key;
	char	*env_value;

	(*i)++;
	env_key = split_keyname(tokenized->token, *i);
	if (!env_key)
		return (false);
	(*i) += ft_strlen(env_key);
	if (env_key[0] == '\0')
		return (free(env_key), true);
	env_value = find_env(condition, env_key);
	free(env_key);
	if (!env_value)
		return (false);
	ft_strjoin_free(new, env_value);
	free(env_value);
	if (!*new)
		return (false);
	return (true);
}

bool	expand_dollar(t_condition *condition, t_token *tokenized)
{
	int		i;
	char	quote;
	char	*new;

	i = 0;
	quote = 0;
	new = ft_strdup("");
	if (!new)
		return (false);
	while (tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]))
			quote = tokenized->token[i];
		if (quote != SINGLE_QUOTE && tokenized->token[i] == '$' && \
				count_envname_len(tokenized->token, i + 1))
			handle_dollar(condition, tokenized, &new, &i);
		else
		{
			append_char(&new, tokenized->token[i]);
			i++;
		}
	}
	free(tokenized->token);
	tokenized->token = new;
	return (true);
}
