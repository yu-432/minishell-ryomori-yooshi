#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"

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

int count_token_until_pipe(t_token *token_list)
{
	int count;
	t_token *current;

	count = 0;
	current = token_list;
	if (current->kind == TOKEN_PIPE)
		return (1);
	while(current && current->kind != TOKEN_PIPE)
	{
		count++;
		current = current->next;
	}
	return (count);
}

bool make_node_argv(t_condition *condition, t_token **token_list, t_node *current_node)
{
	int word_count;
	int i;

	word_count = count_token_until_pipe(*token_list);
	current_node->argv = ft_calloc(word_count + 1, sizeof(char *));
	if(!current_node->argv)
		return(false);
	i = 0;
	while (i < word_count)
	{
		current_node->argv[i] = ft_strdup((*token_list)->token);
		if(!current_node->argv[i])
			return (false);
		i++;
		*token_list = (*token_list)->next;
	}
	current_node->argv[i] = NULL;
	(void)condition;
	return (true);
}

void add_kind_info(t_node *node)
{
	if(ft_strncmp(node->argv[0], "|\0", 2) == 0)
		node->kind = NODE_PIPE;
	else
		node->kind = NODE_CMD;
}

t_node *make_node(t_condition *condition, t_token *token_list)
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
		if(!make_node_argv(condition, &token_list, current->next))//PIPE区切りでargvを作成//redirect未処理
			return (NULL);//free?
		add_kind_info(current->next);
		current->next->prev = current;
	}
	current = head.next;
	return (head.next);
}

