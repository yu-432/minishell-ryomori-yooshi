/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:57:38 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

void	update_quote_status(t_lexer *info, char c)
{
	if (info->quote == 0)
		info->quote = c;
	else if (info->quote == c)
		info->quote = 0;
}

bool	ft_strjoin_free(char **s1, char *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (false);
	new = ft_strjoin(*s1, s2);
	if (!new)
		return (false);
	free(*s1);
	*s1 = new;
	return (true);
}

char	*find_env(t_condition *condition, char *env_key)
{
	t_item	*temp;

	temp = condition->environ;
	if (ft_strncmp(env_key, "?\0", 2) == 0)
		return (ft_itoa(condition->exit_status));
	while (temp)
	{
		if (ft_strncmp(temp->key, env_key, ft_strlen(temp->key) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	(void)condition;
	return (NULL);
}

int	count_envname_len(t_token *tokenized, int *i)
{
	int	len;

	len = 0;
	if (tokenized->token[*i] == '?')
		len++;
	else
		while (ft_isalnum(tokenized->token[*i + len]))
			len++;
	return (len);
}
