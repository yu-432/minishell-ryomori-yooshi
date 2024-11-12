/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:19 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:59:42 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

static bool	init_env_value_new(char **new, char **env_value)
{
	if (!(*env_value))
		*env_value = ft_strdup("");
	if (!(*env_value))
		return (false);
	*new = ft_strdup("");
	if (!(*new))
		return (free(*env_value), false);
	return (true);
}

static bool	replace_env(t_token *token, char *env_value, int env_len)
{
	char	*new;
	int		i;

	new = NULL;
	if (!init_env_value_new(&new, &env_value))
		return (false);
	i = 0;
	while (token->token[i])
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

static bool	handle_dollar(t_condition *condition, t_token *tokenized, \
							t_lexer *info, int *i)
{
	(*i)++;
	info->env_key = ft_substr(tokenized->token, *i, \
						count_envname_len(tokenized, i));
	if (!info->env_key)
		return (false);
	if (info->env_key[0] == '\0')
	{
		(*i)++;
		return (true);
	}
	if (!replace_env(tokenized, find_env(condition, info->env_key), \
			ft_strlen(info->env_key)))
		return (false);
	return (true);
}

bool	expand_dollar(t_condition *condition, t_token *tokenized)
{
	int		i;
	t_lexer	info;

	i = 0;
	ft_memset(&info, 0, sizeof(t_lexer));
	while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
	{
		if (is_quote(tokenized->token[i]))
			update_quote_status(&info, tokenized->token[i]);
		if (tokenized->token[i] == '$' && info.quote != SINGLE_QUOTE)
		{
			if (!handle_dollar(condition, tokenized, &info, &i))
				return (false);
		}
		else
			i++;
	}
	return (true);
}
