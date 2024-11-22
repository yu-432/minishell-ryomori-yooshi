/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:19 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/22 17:42:05 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"

static int	count_envname_len(char *token, int i)
{
	int	len;

	len = 0;
	if (token[i] == '?')
		len++;
	else
		while (token[i] && (ft_isalnum(token[i + len]) || \
					token[i + len] == '_'))
			len++;
	return (len);
}

static char	*split_keyname(char *token, int i)
{
	int	len;

	len = count_envname_len(token, i);
	return (ft_substr(token, i, len));
}

bool	handle_dollar(t_condition *condition, char *token, \
							char **new, int *i)
{
	char	*env_key;
	char	*env_value;

	(*i)++;
	env_key = split_keyname(token, *i);
	if (!env_key)
		return (false);
	(*i) += ft_strlen(env_key);
	if (env_key[0] == '\0')
		return (free(env_key), true);
	env_value = find_env(condition, env_key);
	free(env_key);
	if (!env_value)
		env_value = ft_strdup("");
	if (!ft_strjoin_free(new, env_value))
		return (free(*new), free(env_value), false);
	free(env_value);
	if (!*new)
		return (false);
	return (true);
}
