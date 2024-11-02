#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../libft/libft.h"

t_item *search_dup_key(t_condition *condition, char *key)
{
	t_item *cur;

	if (!condition->environ)
		return (NULL);
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
	t_item *item;

	item = ft_calloc(1, sizeof(t_item));
	if (!item)
		return (NULL);
	return (item);
}