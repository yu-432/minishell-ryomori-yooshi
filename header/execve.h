#ifndef EXECVE_H
# define EXECVE_H

#include "standard.h"
#include "condition.h"
#include "token.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

# define HEREDOC_PROMPT "> "
# define READ 0
# define WRITE 1

typedef enum e_node_kind
{
	NODE_CMD,
	NODE_PIPE
}	t_node_kind;

typedef struct s_node
{
	t_node_kind kind;
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
bool exec_command_pipe(t_condition *condition, t_node *node);
bool is_pipe(char *str);






#endif