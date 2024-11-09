#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

bool set_redirect(t_condition *condition, t_node *node, int i)
{
	t_token_kind kind;
	bool is_success;

	is_success = true;
	kind = get_token_kind(node->argv[i]);
	if(kind == TOKEN_REDIRECT_IN)
		is_success = redirect_in(condition, node, i);
	else if(kind == TOKEN_REDIRECT_OUT)
		is_success = redirect_out(condition, node, i);
	else if(kind == TOKEN_REDIRECT_APPEND)
		is_success = redirect_append(condition, node, i);
	else if(kind == TOKEN_REDIRECT_HEREDOC)
		is_success = redirect_heredoc(condition, node, i);
	if(!is_success)
		return(false);
	return (true);
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
	free(node->argv);
	node->argv = new_argv;
	return (true);
}

