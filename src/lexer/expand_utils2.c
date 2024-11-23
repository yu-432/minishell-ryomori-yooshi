/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/23 14:08:03 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"

bool	ft_strjoin_free(char **s1, char *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (false);
	new = ft_strjoin(*s1, s2);
	if (!new)
		return (false);
	if (*s1)
		free(*s1);
	*s1 = new;
	return (true);
}

char	*find_env(t_condition *condition, char *env_key)
{
	t_item	*temp;

	temp = condition->environ;
	if (!ft_strncmp(env_key, "?\0", 2))
		return (ft_itoa(condition->exit_status));
	while (temp)
	{
		if (!ft_strncmp(temp->key, env_key, ft_strlen(temp->key) + 1))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

bool	append_char(char **str, char c)
{
	char	*new;
	char	join[2];

	join[0] = c;
	join[1] = '\0';
	new = ft_strjoin(*str, join);
	if (!new)
		return (false);
	free(*str);
	*str = new;
	return (true);
}
