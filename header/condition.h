#ifndef CONDITION_H
# define CONDITION_H

#include <signal.h>

#define PROMPT "minishell$ "

typedef struct s_item
{
	char *key;
	char *value;
	struct s_item	*next;
}	t_item;

typedef struct s_condition
{
	t_item	*environ;
	int		exit_status;
}	t_condition;

#endif