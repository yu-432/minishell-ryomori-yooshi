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
	struct s_node *prev;
} t_node;

typedef struct s_exec_info
{
	pid_t *pid;
	int keep_fd;
	int pipe_count;
	int executed_count;
} t_exec_info;

bool run_command(t_condition *condition, t_token *token_list);
bool redirect_in(t_node *node, int i);
bool redirect_out(t_node *node, int i);
bool redirect_append(t_node *node, int i);
bool redirect_heredoc(t_node *node, int i);
bool exec_command(t_condition *condition, t_node *node);
bool is_pipe(char *str);
t_node *make_node(t_token *token_list);
int execute(t_condition *condition, t_node *node);
void reset_fd(int *fd);
void wrap_close(int fd);
void wrap_dup2(int oldfd, int newfd);
void execute_builtin(t_condition *condition, t_node *node);
bool is_builtin(char *cmd);
bool set_redirect_fd(t_node *node);
char **molding_argv(t_node *node);
char	*find_command_path(t_condition *condition, char *command);
t_node *find_last_node(t_node *head);
int count_cmd_arg(t_node *node);
bool is_not_redirect(char *str);
bool close_redirect_fd(t_node *node);
bool set_redirect_fd(t_node *node);
int execute_single_command(t_condition *condition, t_node *node);
pid_t execute_last_pipeline_cmd(t_condition *condition, t_node *node, t_exec_info *info);
bool execute_pipeline_cmd(t_condition *condition, t_node *node, t_exec_info *info);
bool child_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2]);
bool parent_process(t_condition *condition, t_node *node, t_exec_info *info, int fds[2]);
void wrap_double_close(int fd1, int fd2);












#endif