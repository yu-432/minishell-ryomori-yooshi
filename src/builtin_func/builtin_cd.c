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
		perror("strdup");
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
	int		judge;
	char	*env_path;

	env_path = NULL;
	if (option == MOVE_TO_HOME)
		env_path = get_item_value(cond.environ, "HOME");
	else if (option == MOVE_TO_OLDPWD)
		env_path = get_item_value(cond.environ, "OLDPWD");
	if (!env_path)
	{
		perror("cd");
		return (1);
	}
	judge = chdir(env_path);
	return (judge);
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
bool	character_elimination(char **newcwd, char *args, char *element)
{
	size_t	len;

	len = ft_strlen(element);
	if (ft_strncmp(args, element, len) == 0)
	{
		if (args[len] == '\0' || args[len] == '/')
		{
			*newcwd = args + len;
			return (true);
		}
	}
	return (false);
}

void	default_previous_path(char *newcwd)
{
	char	*start;
	char	*previous_history;

	start = newcwd;
	previous_history = NULL;
	while (newcwd)
	{
		if (*newcwd == '/')
		{
			previous_history = newcwd;
			newcwd++;
		}
		if (previous_history != NULL)
			*previous_history = '\0';
	}
}

size_t	strlncpy(char *dst, char *src, size_t n, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && n > 0 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
		n--;
	}
	dst[i] = '\0';
	while (n > 0 && *src)
	{
		i++;
		n--;
		src++;
	}
	return (i);
}
int	append_path(char *dest, size_t destsize, char **newcwd, char *args)
{
	size_t	len;
	char	buf[PATH_MAX];

	len = 0;
	while (args[len] && args[len] != '/')
		len++;
	if (ft_strlcpy (buf, args, len + 1) >= destsize)
	{
		perror("cd");
		return(1);
	}
	if (dest[ft_strlen (dest) - 1] != '/')
		if (ft_strlcat (dest, "/", destsize) >= destsize)
		{
			perror("cd");
			return(1);
		}
	if (ft_strlcat (dest, buf, destsize) >= destsize)
	{
		perror("cd");
		return(1);
	}
	*newcwd = args + len;
	return (0);
}

char	*recreate_cwd(char *pwd, char *args)
{
	char	*newcwd;

	newcwd = (char *)malloc(PATH_MAX);
	if (newcwd == NULL)
	{
		perror("malloc");
		exit(1);
	}
	if (*args == '/' || pwd == NULL)
		ft_strlcpy(newcwd, "/", PATH_MAX);
	else
		ft_strlcpy(newcwd, pwd, PATH_MAX);
	while (*args)
	{
		if (*args == '/')
			args++;
		else if (character_elimination (&args, newcwd, "."))
			;
		else if (character_elimination (&args, newcwd, ".."))
			default_previous_path(newcwd);
		else
			append_path(newcwd, PATH_MAX, &args, args);
	}
	return (newcwd);
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
			perror("strdup");
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
		perror ("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	update_old_pwd(cond);
	update_cwd(cond, cwd);
	return (0);
}
