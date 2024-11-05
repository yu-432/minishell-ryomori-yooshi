#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"

int set_redirect(t_node *node, t_token **token_list)
{
	bool is_success;
	t_token_kind kind;

	is_success = true;
	kind = (*token_list)->kind;
	if(kind == TOKEN_REDIRECT_IN)
		is_success = redirect_in(node, *token_list);
	else if(kind == TOKEN_REDIRECT_OUT)
		is_success = redirect_out(node, *token_list);
	else if(kind == TOKEN_REDIRECT_APPEND)
		is_success = redirect_append(node, *token_list);
	else if(kind == TOKEN_REDIRECT_HEREDOC)
		is_success = redirect_heredoc(node, *token_list);
	if(!is_success)
		return(1);
	*token_list = (*token_list)->next;
	if (!(*token_list))
		return (0);
	*token_list = (*token_list)->next;
	return (0);
}

t_node *new_node(void)
{
	t_node *node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->fd_in = -2;
	node->fd_out = -2;
	return (node);
}

bool is_redirect(t_token_kind kind)
{
	if (kind == TOKEN_REDIRECT_IN || \
		kind == TOKEN_REDIRECT_OUT || \
		kind == TOKEN_REDIRECT_APPEND || \
		kind == TOKEN_REDIRECT_HEREDOC)
		return (true);
	return (false);
}

int count_word_until_pipe(t_token *token_list)
{
	int count;
	t_token *current;

	count = 0;
	current = token_list;
	if (current->kind == TOKEN_PIPE)
		return (1);
	while(current && current->kind != TOKEN_PIPE)
	{
		if (current->kind == TOKEN_WORD)
			count++;
		if (is_redirect(current->kind) && current->next)
			current = current->next->next;
		else
			current = current->next;
	}
	return (count);
}

char **make_node_argv(t_token **token_list, t_node *current_node)
{
	int word_count;
	int i;

	word_count = count_word_until_pipe(*token_list);//TOKEN_WORDの数を数える
	current_node->argv = ft_calloc(word_count + 1, sizeof(char *));
	if(!current_node->argv)
		return(NULL);
	i = 0;
	if ((*token_list)->kind == TOKEN_PIPE)
	{
		current_node->argv[i] = ft_strdup((*token_list)->token);
		if (!current_node->argv[i])
			return (NULL);
		*token_list = (*token_list)->next;
		return (NULL);
	}

	while (i < word_count || (*token_list && (*token_list)->kind != TOKEN_PIPE))
	{
		if (!is_redirect((*token_list)->kind))
		{
			current_node->argv[i] = ft_strdup((*token_list)->token);
			if (!current_node->argv[i])
				return (NULL);
			i++;
			*token_list = (*token_list)->next;
		}
		else if(is_redirect((*token_list)->kind))
			set_redirect(current_node, token_list);
	}
	current_node->argv[i] = NULL;
	return (NULL);////////////////////////
}

t_node *make_node(t_token *token_list)
{
	t_node head;
	t_node *current;

	head.next = NULL;
	while(token_list)
	{
		current = find_last_node(&head);
		current->next = new_node();
		if (!current->next)
			return (NULL);
		make_node_argv(&token_list, current->next);//PIPE区切りでargvを作成
		if (current->next->argv[0] == NULL)
			return (NULL);
		if(ft_strncmp(current->next->argv[0], "|\0", 2) == 0)
			current->next->kind = NODE_PIPE;
		else
			current->next->kind = NODE_CMD;
		current->next->prev = current;
	}
	current = head.next;
	return (head.next);
}

