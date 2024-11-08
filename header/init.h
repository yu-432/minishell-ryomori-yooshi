#ifndef INIT_H
# define INIT_H

bool	init_shell(t_condition *condition, char **envp);
bool init_environ(t_condition *condition, char **envp);
bool add_env(t_condition *condition, char *env_str);
t_item *touch_t_item();
t_item *find_tail(t_item *head);
t_item *search_dup_item(t_condition *condition, char *key);
bool insert_env(t_condition *condition, char *key, char *value);



# endif