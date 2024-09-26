/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:22:32 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/25 17:21:24 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cc execve.c tokenizer.c parser.c libft.a test.h -lreadline -lhistory

#include "test.h"

t_token *token_dup(t_token *token)
{
	char *str;

	str  = ft_strdup(token->token);
	if (!str)
		return (NULL);
	return (new_token(str, token->kind));
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

void append_token(t_token **node_args, t_token *token)
{
	if (*node_args == NULL)
	{
		*node_args = token;
		return ;
	}
	append_token(&(*node_args)->next, token);
}

t_node	*append_node(t_node *node, t_node_kind kind)
{
	t_node *new;

	new = new_node(kind);
	if (!new)
		return (NULL);
	node->next = new;
	return (new);
}

t_node	*find_last_node(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

t_node	*parser(t_token *token)
{
	t_node	*node;
	t_node	*last_node;

	node = new_node(NODE_CMD);
	while (token && token->kind != TOKEN_EOF)
	{
		last_node = find_last_node(node);
		if (token->kind == TOKEN_WORD)
		{
			if (!(last_node->kind == NODE_CMD))
			{
				if(!append_node(last_node, NODE_CMD))
					return (NULL);
				last_node = last_node->next;
			}
			append_token(&last_node->args, token_dup(token));
		}
		if (token->kind == TOKEN_OPE)
		{
			if (!(node->kind == NODE_OPE))
			{
				if (!(append_node(last_node, NODE_OPE)))
					return (NULL);
				last_node = last_node->next;
			}
			append_token(&last_node->args, token_dup(token));
		}
		token = token->next;
	}
	return (node);
}
