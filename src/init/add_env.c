#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/init.h"
#include "../../libft/libft.h"

bool insert_env(t_condition *condition, char *key, char *value)
{
	t_item *new;

	new = touch_t_item();
	if (!new)
		return (false);
	new->key = key;
	new->value = value;
	if (condition->environ == NULL)
	{
		condition->environ = new;
		return (true);
	}
	find_tail(condition->environ)->next = new;
	return (true);
}

static void replace_env(t_item *dup_key_node, char *value, char *key)
{
	free(dup_key_node->value);
	dup_key_node->value = value;
	free(key);
}

bool add_env(t_condition *condition, char *env_str)
{
	char *equal;
	char *key;
	char *value;
	t_item *dup_key_node;

	equal = ft_strchr(env_str, '=');
	if (!equal)
		return (false);
	key = ft_substr(env_str, 0, equal - env_str);
	value = ft_strdup(equal + 1);
	if (!key || !value)
		return (false);
	dup_key_node = search_dup_item(condition, key);
	if (dup_key_node)
		replace_env(dup_key_node, value, key);
	else
		if (!insert_env(condition, key, value))
			return (false);
	return(true);
}
