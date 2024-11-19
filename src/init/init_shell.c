/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:12 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 14:02:04 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/init.h"

void	free_environ(t_item *environ)
{
	t_item	*temp;

	if (!environ)
		return ;
	while (environ)
	{
		temp = environ->next;
		free(environ->key);
		free(environ->value);
		free(environ);
		environ = temp;
	}
}

static bool	get_environ(t_condition *condition, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!add_env(condition, envp[i]))
		{
			free_environ(condition->environ);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_shell(t_condition *condition, char **envp)
{
	condition->envp = envp;
	condition->exit_status = 0;
	condition->environ = NULL;
	if (!get_environ(condition, envp))
		return (false);
	return (true);
}
