/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:50 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:55:51 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"

int count_cmd_arg(t_node *node)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (node->argv[i])
	{
		if (!is_redirect(node->argv[i]) && !is_heredoc(node->argv[i]))
			count++;
		else
			count--;
		i++;
	}
	return (count);
}

static char *take_env_value(t_condition *condition, char *key)
{
	t_item *current;

	current = condition->environ;
	while (current)
	{
		if (!ft_strncmp(current->key, key, strlen(key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*find_command_path(t_condition *condition, char *command)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	if (command[0] == '\0')
		return (ft_strdup(""));
	path = ft_split(take_env_value(condition, "PATH"), ':');
	if (!path)
		path = ft_split(get_item_value(condition->environ, "PWD"), ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", command);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
			return (free(path), joined);
		free(joined);
		i++;
	}
	free(path);
	return (NULL);
}

int count_environ(t_item *environ)
{
	int count;

	count = 0;
	while (environ)
	{
		count++;
		environ = environ->next;
	}
	return (count);
}