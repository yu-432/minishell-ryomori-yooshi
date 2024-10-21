#include "../../header/condition.h"
#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execve.h"
#include "../../libft/libft.h"

int count_pipe(t_node *node)
{
	int count;

	count = 0;
	while (node)
	{
		if (get_token_kind(node->argv[0]) == TOKEN_PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

bool execute_first_command(t_condition *condition, t_node **node, int **fds)
{
	pid_t pid;

	if ((*node)->next == NULL || pipe(&fds) == -1)
		return(false);
	pid = fork();
	if(pid < 0)
		return(false);
	if (pid == 0)
	{
		close(*fds[0]);
		dup2(*fd[1], STDOUT_FILENO);
		close(*fds[1]);
	}

}

bool exec_command_pipe(t_condition *condition, t_node *node)
{
	int fds[2];

	execute_first_command(condition, &node, &fds);
}