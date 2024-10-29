#ifndef BUILTIN_FUNC_H
# define BUILTIN_FUNC_H

#include "condition.h"

void builtin_echo(char **argv);
void builtin_env(t_condition *condition);
void builtin_export(char **argv, t_condition *condition);
void builtin_unset(t_condition *condition, char **argv);

# endif