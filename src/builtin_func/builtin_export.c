#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/init.h"
#include "../../header/builtin_func.h"

bool is_envname(char c)
{
	if(ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void put_export_error(t_condition *condition, char *argv)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	condition->exit_status = 1;
}

char *split_key(t_condition *condition, char *argv)
{
	int i;
	char *key;

	i = 0;
	while(argv[i] && argv[i] != '=')
	{
		if(!is_envname(argv[i]) || (i == 0 && ft_isdigit(argv[i])))
			return (put_export_error(condition, argv), NULL);
		i++;
	}
	if (i == 0)
		return (put_export_error(condition, argv), NULL);
	key = ft_substr(argv, 0, i);
	if (!key)
		return (perror("export"), NULL);
	return (key);
}

char *split_value(char *argv)
{
	char *equal;

	equal = ft_strchr(argv, '=');
	if (!equal)
		return (ft_strdup(""));
	return (ft_substr(equal, 1, ft_strlen(argv) - (equal - argv)));
}

bool split_argv(t_condition *condition, char *argv, char **key_value)
{
	key_value[0] = split_key(condition, argv);
	if(!key_value[0])
		return(false);
	key_value[1] = split_value(argv);
	if(!key_value[1])
		return (free(key_value[0]), perror("export"), false);
	return (true);
}

void builtin_export(t_condition *condition, char **argv)
{
	char *key_value[2];
	t_item *dup_item;

	argv++;
	if (!*argv)
		return (builtin_env(condition));
	while(*argv)
	{
		if(!split_argv(condition, *argv, key_value))
		{
			argv++;
			continue;
		}
		dup_item = search_dup_item(condition, key_value[0]);
		if (dup_item)
		{
			free(key_value[0]);
			free(dup_item->value);
			dup_item->value = key_value[1];
		}
		else
			if(!insert_env(condition, key_value[0], key_value[1]))
				perror("export");
		argv++;
	}
}
