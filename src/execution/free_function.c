#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"

void	free_node(t_node *node)
{
	int	i;

	if (node)
	{
		if (node->argv)
		{
			i = 0;
			while (node->argv[i] != NULL)
			{
				free(node->argv[i]);
				i++;
			}
			free(node->argv);
		}
		if (node->heredoc_str)
			free(node->heredoc_str);
		free(node);
	}
}

void	free_token(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->token);
		free(tmp);
	}
}