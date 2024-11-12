#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/builtin_func.h"
#include "../../libft/libft.h"

char	*lst_getenv(t_item *item, char *key)
{
	char	*value;

	while (item)
	{
		if (ft_strncmp (item->key, key, ft_strlen(key) + 1) == 0)
		{
			value = item->value;
			return (value);
		}
		item = item->next;
	}
	return (NULL);
}

int	update_cwd(t_condition *cond, char *newcwd)
{
	t_item	*item;
	t_item	*old_item;

	item = cond->environ;
	old_item = NULL;
	while (item->next)
	{
		if (ft_strncmp (item->key, "PWD", 4) == 0)
		{
			old_item = item;
			break ;
		}
		item = item->next;
	}
	if (old_item)
	{
		free(old_item->value);
		old_item->value = ft_strdup(newcwd);
		if (old_item->value == NULL)
			return (put_cd_error(cond, NULL, "malloc"), 1);
	}
	return (0);
}
