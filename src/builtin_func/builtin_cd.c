#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"

typedef enum e_move_position
{
	MOVE_TO_HOME,
	MOVE_TO_OLDPWD
}	t_move_position;

//=============================================================================
//==========================        GET_ITEM_VALUE        =======================
//=============================================================================

char *get_item_value(t_item *item, char *key)
{
	char *value;

	while(item)
	{
		if(ft_strncmp(item->key, key, ft_strlen(key) + 1) == 0)
		{
			value = item->value;
			return (value);
		}
		item = item->next;
	}
	return (NULL);
}

//=============================================================================
//==========================        UPDATE_OLD_PWD        =======================
//=============================================================================

static int update_old_pwd(t_condition *cond)
{
	char *cwd;//pathmaxとは？
	t_item *item;
	t_item *old_item;

	item = cond->environ;
	cwd = get_item_value(cond->environ, "PWD");
	old_item = NULL;
	while(item->next)
	{
		if(ft_strncmp(item->key, "OLDPWD", 7) == 0)
		{
			old_item = item;
			break;
		}
		item = item->next;
	}
	if(old_item)
	{
		free(old_item->value);
		old_item->value = ft_strdup(cwd);
		if(old_item->value == NULL)
		{
			perror("strdup");
			return (1);
		}
	}
	return (0);
}

//=============================================================================
//==========================        MOVE_PATH        ==========================
//=============================================================================


static int move_path(int option, t_condition cond)
{
	int judge;
	char *env_path;

	env_path = NULL;
	if(option == MOVE_TO_HOME)
	{
		update_old_pwd(&cond);
		env_path = get_item_value(cond.environ, "HOME");
	}
	else if(option == MOVE_TO_OLDPWD)
	{
		env_path = get_item_value(cond.environ, "OLDPWD");
		update_old_pwd(&cond);
	}
	if(!env_path)
	{
		perror("cd");
		return (1);
	}
	judge = chdir(env_path);
	return (judge);
}

//=============================================================================
//==========================        BUILTIN_CD        ==========================
//=============================================================================

int builtin_cd(t_condition *cond, char **args)
{
	int	judge;
	char newcwd[PATH_MAX];
	char *pwd;

	pwd = lst_getenv(cond, "PWD");
	if(!args[1] || !ft_strncmp(args[1], "~", 2))
		judge = (move_path(MOVE_TO_HOME, *cond));
	if (ft_strncmp(args[1], "-", 2) == 0)
		judge = move_path(MOVE_TO_OLDPWD, *cond);
	else
	{
		update_old_pwd(cond);
		judge = chdir(args[1]);
	}
	if(judge < 0)
		perror("cd");
	newcwd = recreate_cwd(pwd, args[1]);//作成中
	set_newcwd(cond, newcwd);//作成中
	return (0);//success or fail
}

//=============================================================================
//==========================        lst_getenv       ==========================
//=============================================================================

char *lst_getenv(t_item *item, char *key)
{
	char *value;

	while(item)
	{
		if(ft_strncmp(item->key, key, ft_strlen(key) + 1) == 0)
		{
			value = item->value;
			return (value);
		}
		item = item->next;
	}
	return (NULL);
}

//=============================================================================
//==========================        recreate_cwd       ==========================
//=============================================================================

char *recreate_cwd(char *pwd, char *args)
{
	char newcwd[PATH_MAX];
	char *tmp;

	if(*args == '/' || pwd == NULL)
		ft_strlcpy(newcwd, "/", PATH_MAX);
	else
		ft_strlcpy(newcwd, pwd, PATH_MAX);

	while(*args)
	{
		if(*args == '/')
			args++;
		else if(ft_strncmp(args, ".", 3) == 0)
	}
	
	return (newcwd);
}

bool character_elimination(char ***newcwd, char *args, char *element)
{
	size_t len;

	len = ft_strlen(element);
	if (ft_strncmp(args, element, len) == 0)
	{
		if(args[len] == '\0' || args[len] == '/')
		{
			*newcwd = args + len;
			return
		}
	}
	return (false);
}