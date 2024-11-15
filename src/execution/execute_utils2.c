/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:50 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/15 10:31:40 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"

static char	*take_env_value(t_condition *condition, char *key)
{
	t_item	*current;

	current = condition->environ;
	while (current)
	{
		if (!ft_strncmp(current->key, key, strlen(key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

bool	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (true);
	return (false);
}

static char	*search_can_access_path(char **path, char *command)
{
	int		i;
	char	*slash;
	char	*joined;

	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", command);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
		{
			free_argv(path);
			return (joined);
		}
		free(joined);
		i++;
	}
	free_argv(path);
	return (NULL);
}

char	*find_command_path(t_condition *condition, char *command)
{
	char	**path;

	if (command[0] == '\0')
		return (ft_strdup(""));
	path = ft_split(take_env_value(condition, "PATH"), ':');
	if (!path)
		path = ft_split(get_item_value(condition->environ, "PWD"), ':');
	return (search_can_access_path(path, command));
}

	// if (is_path(node->argv[0]))
	// 	path = ft_strdup(node->argv[0]);
	// else
	// 	path = find_command_path(condition, node->argv[0]);

char	*get_path(t_condition *condition, char *command)
{
	if (is_path(command))
		return (ft_strdup(command));
	return (find_command_path(condition, command));
}
