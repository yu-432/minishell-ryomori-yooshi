#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../header/init.h"
#include "../../libft/libft.h"

bool insert_env(t_condition *condition, char *key, char *value)
{
	t_item *new;
	t_item *tail;

	new = touch_t_item();
	if (!new)
	{
		printf("TODO if touch item failed\n");
		return (false);
	}
	new->key = key;
	new->value = value;
	if (condition->environ == NULL)
	{
		condition->environ = new;
		return (true);
	}
	tail = set_tail(condition->environ);
	tail->next = new;
	return (true);
}

bool add_env(t_condition *condition, char *env_str)
{
	char *equal;
	char *key;
	char *value;
	t_item *dup_key;

	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		//TODO:エラー処理
		return (false);
	}
	key = ft_substr(env_str, 0, equal - env_str);
	value = ft_strdup(equal + 1);
	if (!key || !value)
		return (false);//TODO-----------------------
	dup_key = search_dup_key(condition, key);
	if (dup_key)
	{
		free(dup_key->value);
		dup_key->value = value;
		free(key);
	}
	else
		insert_env(condition, key, value);
	return(true);
}
