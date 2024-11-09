#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../header/execution.h"

void reset_fd(int *fd)
{
	if (*fd != -2)
	{
		close(*fd);
		*fd = -2;
	}
}

bool close_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_close(node->fd_in);
		node->fd_in = -2;
	}
	if (node->fd_out != -2)
	{
		wrap_close(node->fd_out);
		node->fd_out = -2;
	}
	return (true);
}

void wrap_double_close(int fd1, int fd2)
{
	wrap_close(fd1);
	wrap_close(fd2);
}

bool set_redirect_fd(t_node *node)
{
	if (node->fd_in != -2)
	{
		wrap_dup2(node->fd_in, STDIN_FILENO);
	}
	if(node->fd_out != -2)
	{
		wrap_dup2(node->fd_out, STDOUT_FILENO);
	}
	close_redirect_fd(node);
	return (false);
}

void storage_fd(int *keep_fds)
{
	keep_fds[IN] = dup(STDIN_FILENO);
	keep_fds[OUT] = dup(STDOUT_FILENO);
	keep_fds[ERR] = dup(STDERR_FILENO);
}

bool restore_fd(int *keep_fds)
{
	wrap_close(STDIN_FILENO);
	wrap_close(STDOUT_FILENO);
	wrap_close(STDERR_FILENO);
	wrap_dup2(keep_fds[IN], STDIN_FILENO);
	wrap_dup2(keep_fds[OUT], STDOUT_FILENO);
	wrap_dup2(keep_fds[ERR], STDERR_FILENO);
	wrap_close(keep_fds[IN]);
	wrap_close(keep_fds[OUT]);
	wrap_close(keep_fds[ERR]);
	return (true);
}