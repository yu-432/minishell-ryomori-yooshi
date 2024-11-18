/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 02:23:45 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"
#include "../../header/builtin_func.h"
#include "../../header/print.h"

static bool	is_envname(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static char	*split_key(t_condition *condition, char *argv)
{
	int		i;
	char	*key;

	i = 0;
	while (argv[i] && argv[i] != '=')
	{
		if (!is_envname(argv[i]) || (i == 0 && ft_isdigit(argv[i])))
			return (put_export_error(condition, argv), NULL);
		i++;
	}
	if (i == 0)
		return (put_export_error(condition, argv), NULL);
	key = ft_substr(argv, 0, i);
	if (!key)
		return (export_error(condition, NULL, "malloc"), NULL);
	return (key);
}

static char	*split_value(char *argv)
{
	char	*equal;

	equal = ft_strchr(argv, '=');
	if (!equal)
		return (ft_strdup(""));
	return (ft_substr(equal, 1, ft_strlen(argv) - (equal - argv)));
}

static bool	split_argv(t_condition *condition, char *argv, char **key_value)
{
	key_value[0] = split_key(condition, argv);
	if (!key_value[0])
		return (false);
	key_value[1] = split_value(argv);
	if (!key_value[1])
		return (free(key_value[0]),
			export_error(condition, NULL, "malloc"), false);
	return (true);
}

void	builtin_export(t_condition *condition, char **argv)
{
	char	*key_value[2];
	t_item	*dup_item;

	argv++;
	if (check_condition(condition, argv))
		return ;
	while (*argv)
	{
		if (!split_argv(condition, *argv, key_value))
		{
			argv++;
			continue ;
		}
		dup_item = search_dup_item(condition, key_value[0]);
		if (dup_item)
		{
			free(key_value[0]);
			free(dup_item->value);
			dup_item->value = key_value[1];
		}
		else
			if (!insert_env(condition, key_value[0], key_value[1]))
				export_error(condition, NULL, "calloc");
		argv++;
	}
}
