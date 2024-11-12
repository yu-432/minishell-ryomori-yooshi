/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:38 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:55:40 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"

void	free_t_item(t_item **item)
{
	free((*item)->key);
	free((*item)->value);
	free(*item);
}

t_item	*search_prev_item(t_condition *condition, t_item *dup_item)
{
	t_item	*current;

	current = condition->environ;
	if (current == dup_item)
		return (NULL);
	while (current->next)
	{
		if (current->next == dup_item)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	builtin_unset(t_condition *condition, char **argv)
{
	int		i;
	t_item	*delete_item;
	t_item	*prev_item;

	i = 1;
	while (argv[i])
	{
		delete_item = search_dup_item(condition, argv[i]);
		if (!delete_item)
		{
			i++;
			continue ;
		}
		prev_item = search_prev_item(condition, delete_item);
		if (!prev_item)
			condition->environ = delete_item->next;
		else
			prev_item->next = delete_item->next;
		free_t_item(&delete_item);
		i++;
	}
}
