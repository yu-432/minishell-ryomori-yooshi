#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/builtin_func.h"
#include "../../libft/libft.h"

char	*get_item_value(t_item *item, char *key)
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

int	update_item_value(t_condition *cond, t_item *item, const char *cwd)
{
	free(item->value);
	item->value = ft_strdup(cwd);
	if (item->value == NULL)
		return (put_cd_error(cond, NULL, "malloc"), 1);
	return (0);
}

int	update_old_pwd(t_condition *cond)
{
	char	*cwd;
	t_item	*item;
	t_item	*old_item;

	item = cond->environ;
	cwd = get_item_value(cond->environ, "PWD");
	if (cwd == NULL)
		return (0);
	old_item = NULL;
	while (item->next)
	{
		if (ft_strncmp (item->key, "OLDPWD", 7) == 0)
		{
			old_item = item;
			break ;
		}
		item = item->next;
	}
	if (old_item)
	{
		return (update_item_value(cond, old_item, cwd));
	}
	return (0);
}

int	move_path(int option, t_condition cond)
{
	char	*env_path;

	env_path = NULL;
	if (option == MOVE_TO_HOME)
		env_path = getenv("HOME");
	else if (option == MOVE_TO_OLDPWD)
	{
		env_path = get_item_value(cond.environ, "OLDPWD");
		if (!env_path)
			return (1);
	}
	return (chdir(env_path));
}

int	builtin_cd(t_condition *cond, char **args)
{
	int		judge;
	char	cwd[PATH_MAX];

	if (args[2])
		return (put_cd_error(cond, "too many arguments", NULL), 1);
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		judge = move_path(MOVE_TO_HOME, *cond);
	else if (ft_strncmp(args[1], "-", 2) == 0)
		judge = move_path(MOVE_TO_OLDPWD, *cond);
	else
		judge = chdir(args[1]);
	if (judge != 0)
	{
		if (!args[1] || ft_strncmp(args[1], "-", 2) == 0)
			return (put_cd_error(cond, "OLDPWD not found", NULL), 1);
		else
			return (put_cd_error(cond, NULL, "chdir"), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (put_cd_error(cond, NULL, "getcwd"), 1);
	update_old_pwd(cond);
	update_cwd(cond, cwd);
	return (0);
}
