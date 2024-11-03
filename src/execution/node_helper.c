#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"

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
