#ifndef INIT_H
# define INIT_H

int	init_shell(t_condition *condition, char **argv, char **envp);
bool init_environ(t_condition *condition, char **envp);

# endif