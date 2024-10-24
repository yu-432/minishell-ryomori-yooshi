#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"

t_node *new_node(char **argv)
{
	t_node *node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->argv = argv;
	node->fd_in = -2;
	node->fd_out = -2;
	node->heredoc_str = NULL;
	return (node);
}

int count_until_pipe(t_token *token_list)
{
	int count;
	t_token *current;

	count = 0;
	current = token_list;
	if (current->kind == TOKEN_PIPE)
		return (1);
	while(current)
	{
		if(current->kind ==TOKEN_PIPE)
			break;
		count++;
		current = current->next;
	}
	return (count);
}


char **make_argv(t_token **token_list)
{
	char **argv;
	int arg_count;
	int i;

	arg_count = count_until_pipe(*token_list);
	argv = ft_calloc(arg_count + 1, sizeof(char *));
	if(!argv)
		return(NULL);
	i = 0;
	while (i < arg_count)
	{
		argv[i] = ft_strdup((*token_list)->token);
		if (!argv[i])
			return (NULL);
		*token_list = (*token_list)->next;
		i++;
	}
	argv[i] = NULL;

	int j = 0;
	while (argv[j])
	{
		printf("argv[%d] = %s\n", j, argv[j]);
		j++;
	}
	return (argv);
}

t_node *find_last_node(t_node *head)
{
	while(head->next)
		head = head->next;
	return (head);
}

bool is_pipe(char *str)
{
	if (!ft_strncmp(str, "|\0", 2))
		return (true);
	return (false);
}

t_node *make_node(t_token *token_list)
{
	t_node head;
	t_node *current;
	char **argv;
	int i;

	i = 0;
	head.next = NULL;
	while(token_list)
	{
		current = find_last_node(&head);
		argv = make_argv(&token_list);
		if (!argv)
			return (NULL);
		current->next = new_node(argv);
		if (!current->next)
			return (NULL);
		if (is_pipe(argv[0]))
			current->next->kind = NODE_PIPE;
		else
			current->next->kind = NODE_CMD;
	}
	return (head.next);
}

