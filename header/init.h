#ifndef INIT_H
# define INIT_H

#include <stdio.h>

int	init_shell(t_condition *condition, char **argv, char **envp);
int init_environ(t_condition *condition, char **envp);

# endif