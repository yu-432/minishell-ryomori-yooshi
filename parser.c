/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:22:32 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/22 12:46:14 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_token *token_dup(t_token *token)
{
	char *str;

	str  = ft_strdup(token->token);
	if (!str)
		return (NULL);
	return (new_token(str, token->kind));
}

void append_token(t_token **node_args, t_token *token)
{
	if (*node_args == NULL)
	{
		*node_args = token;
		return ;
	}
	append_token(&(*node_args)->next, token);
}

t_node  *new_node(t_node_kind kind)
{
	t_node *new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->kind = kind;
	new->next = NULL;
	return (new);
}

t_node	*parser(t_token *token)
{
	t_node *node;

	node = new_node(NODE_SIMPLE_CMD);
	while (token && token->kind != TOKEN_EOF)
	{
		if (token->kind == TOKEN_WORD)
		{
			append_token(&node->args, token_dup(token));
		}
		else
			printf("今後作ります\n");
		token = token->next;
	}
	return (node);
}