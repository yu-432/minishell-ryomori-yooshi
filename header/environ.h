#ifndef ENVIRON_H
# define ENVIRON_H

bool add_env(t_condition *condition, char *env_str);
t_item *touch_t_item();
t_item *set_tail(t_item *head);
t_item *serch_dup_key(t_condition *condition, char *key);



# endif