#ifndef CONDITION_H
# define CONDITION_H

#include <signal.h>

#define PROMPT "minishell$ "

extern pid_t g_foreground_pid;


typedef struct s_item
{
	char *key;
	char *value;
	struct s_item	*next;
	struct s_item	*prev;
}	t_item;

typedef struct s_condition
{
	// char	*shell_name;
	t_item	*environ;
	char	*cwd;
	int		exit_status;
}	t_condition;

#endif