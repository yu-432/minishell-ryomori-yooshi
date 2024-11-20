/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:45 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 13:59:06 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

void	free_exit(t_condition *condition, t_node *node, char *path, \
					int exit_status)
{
	if (condition)
		free_argv(condition->envp);
	if (node)
	{
		while (node->prev)
			node = node->prev;
		free_node(node);
	}
	free(path);
	exit(exit_status);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return ;
}
