#include "../../header/token.h"
#include "../../header/node.h"
#include "../../header/execution.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"
#include "../../header/signal.h"

bool parent_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2])
{
	// setup_parent_signal();//
	wrap_close(fds[WRITE]);
	if (info->keep_fd != -2)
		wrap_close(info->keep_fd);
	info->keep_fd = fds[READ];
	(void)condition;
	(void)node;
	(void)info;
	return (true);
}

bool child_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2])
{
	setup_child_signal();
	if (info->executed_count < info->pipe_count)
	{
		wrap_dup2(fds[WRITE], STDOUT_FILENO);
		wrap_close(fds[WRITE]);
		wrap_close(fds[READ]);
	}
	if (info->executed_count > 0)
	{
		wrap_dup2(info->keep_fd, STDIN_FILENO);
		wrap_close(info->keep_fd);
	}
	execute(condition, node);
	exit(EXIT_FAILURE);
}
