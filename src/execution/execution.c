#include "../../header/execution.h"
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

void set_redirect(t_node *node)
{
	int i;
	bool is_success;
	t_token_kind kind;

	is_success = true;
	while(node)
	{
		i = 0;
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

bool execution_command(t_condition *condition, t_token *token_list)
{
	t_node *node;
	// init 必要かもしれないa
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
	
	exec_command(condition, node);
	(void)condition;
	return (true);
}
