#include "../../header/execve.h"
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"


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

t_node *find_last_node(t_node *head)
{
	while(head->next)
		head = head->next;
	return (head);
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
	return (argv);
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



void set_redirect(t_node *node)
{
	int i;
	bool is_success;
	t_token_kind kind;

	i = 0;
	is_success = true;
	while(node)
	{
		while(node->argv[i])
		{
			kind = get_token_kind(node->argv[i]);
			if(kind == TOKEN_REDIRECT_IN)
				is_success = redirect_in(node, i);
			else if(kind == TOKEN_REDIRECT_OUT)
				is_success = redirect_out(node, i);
			else if(kind == TOKEN_REDIRECT_APPEND)
				is_success = redirect_append(node, i);
			else if(kind == TOKEN_REDIRECT_HEREDOC)
				is_success = redirect_heredoc(node, i);
			if(!is_success)
				put_error("redirect error");
			i++;
		}
		node = node->next;
	}
}

bool execve_command(t_condition *condition, t_token *token_list)
{
	t_node *node;
	t_token *head;

	// init 必要かもしれないa
	head = token_list;
	node = make_node(token_list);
	if (node == NULL)
		return (false);
	set_redirect(node);

	t_node *temp = node;
	while(temp)
	{
		printf("-------------------------\n");
		printf("redirect in = %d, redirect out = %d\n", temp->fd_in, temp->fd_out);
		printf("heredoc_str = %s\n", temp->heredoc_str);
		for (int i = 0; temp->argv[i]; i++)
			printf("argv[%d] = %s\n", i, temp->argv[i]);
		temp = temp->next;
		printf("-------------------------\n");
	}

	exec_command_pipe(condition, node);
	(void)condition;
	return (true);
}
