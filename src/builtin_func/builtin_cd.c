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

int	update_item_value(t_item *item, const char *cwd)
{
	free(item->value);
	item->value = ft_strdup(cwd);
	if (item->value == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror("malloc");
		return (1);
	}
	return (0);
}

static int	update_old_pwd(t_condition *cond)
{
	char	*cwd;
	t_item	*item;
	t_item	*old_item;

	item = cond->environ;
	cwd = get_item_value(cond->environ, "PWD");
	if(cwd == NULL)
		return (0);
	old_item = NULL;
	while (item->next)
	{
		if(ft_strncmp (item->key, "OLDPWD", 7) == 0)
		{
			old_item = item;
			break ;
		}
		item = item->next;
	}
	if (old_item)
	{
		return (update_item_value(old_item, cwd));
	}
	return (0);
}

static int	move_path (int option, t_condition cond)
{
	char	*env_path;

	env_path = NULL;
	if (option == MOVE_TO_HOME)
		env_path = getenv("HOME");
	else if (option == MOVE_TO_OLDPWD)
	{
		env_path = get_item_value(cond.environ, "OLDPWD");
		if(!env_path)
			return(1);
	}
	return (chdir(env_path));
}

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
		if	(ft_strncmp (item->key, "PWD", 4) == 0)
		{
			old_item = item;
			break;
		}
		item = item->next;
	}
	if (old_item)
	{
		free(old_item->value);
		old_item->value = ft_strdup(newcwd);
		if (old_item->value == NULL)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror("malloc");
			return (1);
		}
	}
	return (0);
}

int	builtin_cd(t_condition *cond, char **args)
{
	int		judge;
	char	cwd[PATH_MAX];

	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		judge = move_path(MOVE_TO_HOME, *cond);
	else if (ft_strncmp(args[1], "-", 2) == 0)
		judge = move_path(MOVE_TO_OLDPWD, *cond);
	else
		judge = chdir(args[1]);
	if (judge != 0)
	{ 
		if(!args[1] || ft_strncmp(args[1], "-", 2) == 0)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror("cd");
		}
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror("getcwd");
		return (1);
	}
	update_old_pwd(cond);
	update_cwd(cond, cwd);
	return (0);
}
