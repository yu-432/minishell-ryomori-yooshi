/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:25 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:01:38 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

t_node	*find_last_node(t_node *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

bool	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|\0", 2))
		return (true);
	return (false);
}

void	free_node(t_node *node)
{
	int		i;
	t_node	*temp;

	while (node)
	{
		temp = node->next;
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
		close_redirect_fd(node);
		free(node);
		node = temp;
	}
}

t_node	*new_node(void)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->fd_in = INVALID_FD;
	node->fd_out = INVALID_FD;
	return (node);
}
