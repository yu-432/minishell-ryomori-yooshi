#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../libft/libft.h"

int find_equal_index(char *env_str)
{
	int end;

	end = 0;
	while(env_str[end] != '=' || env_str[end])
		end++;
	if (env_str[end] != '=')
		return (-1);
	return (end);
}

t_item *serch_dup_key(t_condition *condition, char *key)
{
	t_item *cur;

	cur = condition->environ;
	while (cur)
	{
		if (cur->key == key)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_item *set_tail(t_item *head)
{
	t_item *tail;

	tail = head;
	while (tail)
	{
		if (!tail->next)
			break ;
		tail = tail->next;
	}
	return(tail);
}

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
	tail = set_tail(condition->environ);
	tail->next = new;
	return (true);
}

int add_env(t_condition *condition, char *env_str)
{
	char *equal;
	char *key;
	char *value;
	t_item *dup_key;

	//変数に被りがあった場合の挙動を確かめてそれに合わせる必要がある
	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		return (0);
	// if qual == NULL見つからない場合はあまり考えられない
	//　exportが失敗していた場合、初期化の時点ではあまり考えられない
	// 構文エラーで設定されないと思う多分
	}
	key = ft_substr(env_str, 0, equal - env_str);
	value = ft_strdup(equal + 1);
	if (!key || !value)
		return (-1);//TODO-----------------------
	dup_key = serch_dup_key(condition, key);
	if (dup_key)
	{
		printf("dup test");
		//TODO:重複があったばいにvalueのみ上書きする
		//今後export関数を作成するタイミングで編集する
	}
	insert_env(condition, key, value);
	return(0);
}

t_item *touch_t_item()
{
	t_item *head;

	head = ft_calloc(1, sizeof(t_item));
	if (!head)
	{
		printf("touch environ malloc error\n");
		return (NULL);
	}
	return (head);
}