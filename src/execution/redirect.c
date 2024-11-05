#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../header/execution.h"

bool redirect_in(t_node *node, t_token *token_list)
{
	int fd;

	reset_fd(&node->fd_in);
	if (token_list->next== NULL)
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(token_list->next->token, O_RDONLY);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return(false);
	}
	node->fd_in = fd;
	if(node->heredoc_str)
	{
		free(node->heredoc_str);
		node->heredoc_str = NULL;
	}
	return (true);
}

bool redirect_out(t_node *node, t_token *token_list)
{
	int fd;

	reset_fd(&node->fd_out);
	if (token_list->next == NULL)
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(token_list->next->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	if(node->fd_out != -2)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}

bool redirect_append(t_node *node, t_token *token_list)
{
	int fd;

	reset_fd(&node->fd_out);
	if (!token_list->token)
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	fd = open(token_list->next->token, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		put_error(strerror(errno));
		return (false);
	}
	if(node->fd_out != -2)
		close(node->fd_out);
	node->fd_out = fd;
	return (true);
}