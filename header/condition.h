#ifndef CONDITION_H
# define CONDITION_H

#include <errno.h>

typedef struct s_item
{
	char *name;
	char *value;
	t_list	*next;
}	t_list;

typedef struct s_condition
{
	// char	*shell_name;
	t_list	*environ;
	char	*cwd;
	int		exit_status;
}	t_condition;

#endif