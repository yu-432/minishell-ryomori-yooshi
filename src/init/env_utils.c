/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 14:02:00 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/init.h"

t_item	*search_dup_item(t_condition *condition, char *key)
{
	t_item	*cur;

	if (!condition->environ)
		return (NULL);
	cur = condition->environ;
	while (cur)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(key) + 1))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_item	*find_tail(t_item *head)
{
	t_item	*tail;

	tail = head;
	while (tail)
	{
		if (!tail->next)
			break ;
		tail = tail->next;
	}
	return (tail);
}

t_item	*touch_t_item(void)
{
	t_item	*item;

	item = ft_calloc(1, sizeof(t_item));
	if (!item)
		return (NULL);
	return (item);
}
