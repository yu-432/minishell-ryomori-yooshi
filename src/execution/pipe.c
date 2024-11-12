/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:34 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:56:35 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

bool set_redirect(t_condition *condition, t_node *node, int i)
{
	t_token_kind kind;

	kind = get_token_kind(node->argv[i]);
	if(kind == TOKEN_REDIRECT_IN)
		return (redirect_in(condition, node, i));
	else if(kind == TOKEN_REDIRECT_OUT)
		return (redirect_out(condition, node, i));
	else if(kind == TOKEN_REDIRECT_APPEND)
		return (redirect_append(condition, node, i));
	return (false);
}

bool find_set_redirect(t_condition *condition, t_node *node)
{
	int i;

	i = 0;
	while(node->argv[i])
	{
		if (is_pipe(node->argv[0]))
			break;
		if (is_redirect(node->argv[i]))
		{
			if(!set_redirect(condition, node, i))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

void free_node_argv(t_node *node)
{
	int i;

	i = 0;
	while(node->argv[i])
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
}

char **molding_argv(t_node *node)
{
	char **res;
	int count;
	int i;
	int j;

	count = count_cmd_arg(node);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		while (node->argv[j] && node->argv[j][0] == '\0')
			j++;
		if (!node->argv[j])
			break;
		if (!is_redirect(node->argv[j]))
			res[i++] = ft_strdup(node->argv[j]);
		else
			j++;
		j++;
	}
	return (res);
}

bool interpret_redirect(t_condition *condition, t_node *node)
{
	char **new_argv;
	int i;

	i = 0;
	if(!find_set_redirect(condition, node))
		return (false);
	new_argv = molding_argv(node);
	if (!new_argv)
		return (false);
	free_node_argv(node);
	node->argv = new_argv;
	(void)condition;
	return (true);
}

