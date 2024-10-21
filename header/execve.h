#ifndef EXECVE_H
# define EXECVE_H

#include "standard.h"
#include "condition.h"
#include "token.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define HEREDOC_PROMPT "> "

typedef struct s_node
{
	char **argv;
	char *heredoc_str;
	int fd_in;
	int fd_out;
	struct s_node *next;
} t_node;

bool execve_command(t_condition *condition, t_token *token_list);
bool redirect_in(t_node *node, int i);
bool redirect_out(t_node *node, int i);
bool redirect_append(t_node *node, int i);
bool redirect_heredoc(t_node *node, int i);




#endif