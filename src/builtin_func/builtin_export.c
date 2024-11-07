#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"

bool split_argv(char *argv, char **key_value)
{
	int i;

	i = 0;
	while (argv[i] != '=' && argv[i + 1])
		i++;
	key_value[0] = ft_substr(argv, 0, i);
	if(key_value[0] == NULL)
		return (false);
	key_value[1] = ft_substr(argv, i + 1, ft_strlen(argv) - i - 1);//ab, ab= などの場合バグが発生する可能性あり
	if(key_value[1] == NULL)
		return (free(key_value[0]), false);
	return (true);
}

t_item *search_key(t_condition *condition, char *key)
{
	t_item *current;

	current = condition->environ;
	while (current->next)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key)))
			return (current);
		current = current->next;
	}
	return (current);
}
//2つの変数をexportする場合、１つ目で失敗しても最後まで動作を続ける
void builtin_export(t_condition *condition, char **argv)
{
	char *key_value[2];
	t_item *searched_key;

	while(*argv)
	{
		if(!split_argv(*argv, key_value))
		{
			argv++;
			continue;
		}
		searched_key = search_key(condition, key_value[0]);
		if (!ft_strncmp(searched_key->key, key_value[0], ft_strlen(key_value[0])))
		{
			free(key_value[0]);
			free(searched_key->value);
			searched_key->value = key_value[1];
		}
		else
			if(!insert_env(condition, key_value[0], key_value[1]))
				perror("export");
		argv++;
	}

}
