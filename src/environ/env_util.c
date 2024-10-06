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