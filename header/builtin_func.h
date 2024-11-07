#ifndef BUILTIN_FUNC_H
# define BUILTIN_FUNC_H

#include "condition.h"
#include <limits.h>
#include <sys/stat.h>

typedef enum e_move_position
{
	MOVE_TO_HOME,
	MOVE_TO_OLDPWD
}	t_move_position;

void builtin_echo(t_condition *condition, char **argv);
void builtin_env(t_condition *condition);
void builtin_export(t_condition *condition, char **argv);
void builtin_unset(t_condition *condition, char **argv);
int builtin_pwd(t_condition *cond, char **argv);
int builtin_cd(t_condition *cond, char **args);
int	builtin_exit(t_condition *condition, char **args);
char *get_item_value(t_item *item, char *key);

# endif