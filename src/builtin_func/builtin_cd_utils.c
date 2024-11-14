/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_until.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:03 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:55:04 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/builtin_func.h"
#include "../../libft/libft.h"

char	*lst_getenv(t_item *item, char *key)
{
	char	*value;

	while (item)
	{
		if (ft_strncmp (item->key, key, ft_strlen(key) + 1) == 0)
		{
			value = item->value;
			return (value);
		}
		item = item->next;
	}
	return (NULL);
}

int	update_cwd(t_condition *cond, char *newcwd)
{
	t_item	*item;
	t_item	*old_item;
	char	*tmp;

	item = cond->environ;
	old_item = NULL;
	while (item->next)
	{
		if (ft_strncmp (item->key, "PWD", 4) == 0)
		{
			old_item = item;
			break ;
		}
		item = item->next;
	}
	if (old_item)
	{
		tmp = ft_strdup(newcwd);
		if (tmp == NULL)
			return (put_cd_error(cond, NULL, "malloc"), 1);
		if (old_item->value != NULL)
			free(old_item->value);
		old_item->value = tmp;
	}
	return (0);
}

int	count_cd_arg(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
