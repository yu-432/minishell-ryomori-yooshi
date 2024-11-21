/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:09 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:12:11 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/init.h"

bool	insert_env(t_condition *condition, char *key, char *value)
{
	t_item	*new;

	new = touch_t_item();
	if (!new)
		return (false);
	new->key = key;
	new->value = value;
	if (condition->environ == NULL)
	{
		condition->environ = new;
		return (true);
	}
	find_tail(condition->environ)->next = new;
	return (true);
}

static void	replace_env(t_item *dup_key_node, char *key, char *value)
{
	free(key);
	free(dup_key_node->value);
	dup_key_node->value = value;
}

static void	increment_shlvl(char **value)
{
	int		shlvl;
	char	*new_value;

	shlvl = ft_atoi(*value);
	shlvl++;
	if (shlvl > SHLVL_MAX)
	{
		ft_putstr_fd("minishell: warning: shell level (1000) too high,", \
			STDERR_FILENO);
		ft_putstr_fd(" resetting to 1\n", STDERR_FILENO);
		shlvl = 1;
	}
	free(*value);
	new_value = ft_itoa(shlvl);
	if (!new_value)
		return ;
	*value = new_value;
}

bool	add_env(t_condition *condition, char *env_str)
{
	char	*equal;
	char	*key;
	char	*value;
	t_item	*dup_key_node;

	equal = ft_strchr(env_str, '=');
	if (!equal)
		return (false);
	key = ft_substr(env_str, 0, equal - env_str);
	if (!key)
		return (false);
	value = ft_strdup(equal + 1);
	if (value && !ft_strncmp(key, "SHLVL", 6))
		increment_shlvl(&value);
	if (!value)
		return (free(key), false);
	dup_key_node = search_dup_item(condition, key);
	if (dup_key_node)
		replace_env(dup_key_node, key, value);
	else
		if (!insert_env(condition, key, value))
			return (false);
	return (true);
}
