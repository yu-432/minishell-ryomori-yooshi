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
	int fds[2];
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct s_exec_info
{
	int fds[2];
	int keep_fd;
	int pipe_count;
} t_exec_info;

bool execution_command(t_condition *condition, t_token *token_list);
bool redirect_in(t_node *node, int i);
bool redirect_out(t_node *node, int i);
bool redirect_append(t_node *node, int i);
bool redirect_heredoc(t_node *node, int i);
bool exec_command(t_condition *condition, t_node *node);
bool is_pipe(char *str);
t_node *make_node(t_token *token_list);
bool execute(t_condition *condition, t_node *node);
void reset_fd(int *fd);
void wrap_close(int fd);
void wrap_dup2(int oldfd, int newfd);







#endif