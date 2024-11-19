/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:09 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 09:52:17 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/init.h"
#include "../../libft/libft.h"
#include "../../header/print.h"

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

static void	increment_shelvl(char **value)
{
	int		shelvl;
	char	*new_value;

	shelvl = ft_atoi(*value);
	shelvl++;
	if (shelvl > 999)
	{
		put_error("minishell: warning: shell level (1000) too high,");
		put_error(" resetting to 1");
		shelvl = 1;
	}
	free(*value);
	new_value = ft_itoa(shelvl);
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
		increment_shelvl(&value);
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
