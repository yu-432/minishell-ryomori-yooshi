#ifndef BUILTIN_FUNC_H
# define BUILTIN_FUNC_H

#include "condition.h"
#include <limits.h>
#include <sys/stat.h>

void builtin_echo(t_condition *condition, char **argv);
void builtin_env(t_condition *condition);
void builtin_export(t_condition *condition, char **argv);
void builtin_unset(t_condition *condition, char **argv);
int builtin_pwd(t_condition *cond, char **argv);
int builtin_cd(t_condition *cond, char **args);
int	builtin_exit(t_condition *condition, char **args);
char *get_item_value(t_item *item, char *key);

# endif