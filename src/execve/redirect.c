#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../header/execve.h"

bool redirect_in(t_node *node, int i)
{
	int fd;

	if (node->argv[i + 1] == NULL)
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_RDONLY);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return(false);
	}
	node->fd_in = fd;
	return (true);
}

bool redirect_out(t_node *node, int i)
{
	int fd;

	if (node->argv[i + 1] == NULL)
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	node->fd_out = fd;
	return (true);
}

bool redirect_append(t_node *node, int i)
{
	int fd;

	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(node->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	node->fd_out = fd;
	return (true);
}