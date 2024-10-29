#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/environ.h"

void free_t_item(t_item **item)
{
	free((*item)->key);
	free((*item)->value);
	free(*item);
}

void builtin_unset(t_condition *condition, char **argv)
{
	int i;
	t_item *delete_key;

	i = 1;
	while(argv[i])
	{
		delete_key = search_dup_key(condition, argv[i]);
		if (!delete_key)
		{
			i++;
			continue;
		}
		delete_key->prev->next = delete_key->next;
		delete_key->next->prev = delete_key->prev;
		free_t_item(&delete_key);
		i++;
	}
	exit(0);
}