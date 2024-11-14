/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:28 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 23:42:48 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "standard.h"
# include "condition.h"
# include "token.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# define HEREDOC_PROMPT "> "
# define INPUT_EOF 1

typedef enum e_std_fd
{
	IN,
	OUT,
	ERR
}	t_std_fd;

typedef enum e_node_kind
{
	NODE_CMD,
	NODE_PIPE
}	t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	char			**argv;
	int				fd_in;
	int				fd_out;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_exec_info
{
	pid_t	*pid;
	int		keep_fd;
	int		pipe_count;
	int		executed_count;
}	t_exec_info;

//run_command
void	run_command(t_condition *condition, t_token *token_list);
bool	is_redirect(char *str);
bool	is_heredoc(char *str);

//execute
int		execute(t_condition *condition, t_node *node);
void	execute_builtin(t_condition *condition, t_node *node);
bool	is_builtin(char *cmd);
bool	is_kind_redirect(t_token_kind kind);
bool	is_executable(char *path);
bool	is_path(char *cmd);
int		count_cmd_arg(t_node *node);
int		count_environ(t_item *environ);
char	*find_command_path(t_condition *condition, char *command);
void	free_argv(char **argv);

//single_command
int		execute_single_command(t_condition *condition, t_node *node);
void	wait_child_status(t_condition *condition, pid_t pid);

//multi_command
bool	execute_pipeline_cmd(t_condition *condition, t_node *node, \
								t_exec_info *info);
pid_t	execute_last_pipeline_cmd(t_condition *condition, t_node *node, \
									t_exec_info *info);
bool	child_process(t_condition *condition, t_node *node, \
						t_exec_info *info, int fds[2]);
bool	parent_process(t_condition *condition, t_node *node, \
						t_exec_info *info, int fds[2]);

//redirect
bool	redirect_in(t_condition *condition, t_node *node, int i);
bool	redirect_out(t_condition *condition, t_node *node, int i);
bool	redirect_append(t_condition *condition, t_node *node, int i);
bool	set_redirect(t_condition *condition, t_node *node, int i);
bool	interpret_redirect(t_condition *condition, t_node *node);

//heredoc
bool	exec_heredoc(t_condition *condition, t_node *node);
char	*get_line(int fd, int *input_status);

//fd_manager
void	reset_fd(int *fd);
bool	close_redirect_fd(t_node *node);
void	wrap_double_close(int fd1, int fd2);
bool	set_redirect_fd(t_node *node);
void	storage_fd(int *keep_fds);
bool	restore_fd(int *keep_fds);
void	close_child_process_fd(t_node *node);
void close_prev_node_fd(t_node *node);

//node
t_node	*make_node(t_condition *condition, t_token *token_list);
t_node	*new_node(void);
void	free_node(t_node *node);
t_node	*find_last_node(t_node *head);
bool	is_pipe(char *str);

//set
void	set_exit_status_by_signal(int status);
void	set_exit_status_by_status(t_condition *condition, int status);

//wrap
void	wrap_close(int fd);
void	wrap_dup2(int oldfd, int newfd);

#endif