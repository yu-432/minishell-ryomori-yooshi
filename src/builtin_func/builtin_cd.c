
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "condition.h"

//=============================================================================
//==========================        UPDATE_OLD_PWD        =======================
//=============================================================================

static int update_old_pwd(t_condition *cond)
{
	char cwd[PATH_MAX];
	t_item *item;
	t_item *old_item;

	item = cond->environ;

	if(getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	while(item)
	{
		if(strcmp(item->key, "OLDPWD") == 0)
		{
			old_item = item;
			break;
		}
		item = item->next;
	}
	if(old_item)
	{
		free(old_item->value);
		old_item->value = strdup(cwd);
		if(old_item->value == NULL)
		{
			perror("strdup");
			return (1);
		}
	}
}
//=============================================================================
//==========================        GET_ITEM_VALUE        =======================
//=============================================================================

static char *get_item_value(t_item *item, char *key)
{
	char *value;

	while(item)
	{
		if(strcmp(item->key, key) == 0)
		{
			value = item->value;
			return (value);
		}
		item = item->next;
	}
	return (NULL);
}

//=============================================================================
//==========================        MOVE_PATH        ==========================
//=============================================================================


static int move_path(int option, t_condition cond)
{
	int judge;
	char *env_path;

	if(option == 0)
	{
		update_old_pwd(&cond);
		env_path = get_item_value(cond.environ, "HOME");
		if(!env_path)
		{
			perror("get_item_value");
			return (1);
		}
	}
	else if(option == 1)
	{
		env_path = get_item_value(cond.environ, "OLDPWD");
		if(!env_path)
		{
			perror("get_item_value");
			return (1);
		}
	}
	judge = chdir(getenv(env_path));
	return (judge);
}

//=============================================================================
//==========================        BUILTIN_CD        ==========================
//=============================================================================

int builitin_cd(char **args, t_condition *cond)
{
	int	judge;

	if(!args[1] || args[1] == '~')
	{
		return(move_path(0, *cond));
	}
	if (strcmp(args[1] == '-') == 0)
	{
		judge = move_path(1, *cond);
	}
	else
	{
		update_old_pwd(cond);
		judge = chdir(args[1]);
		if(judge < 0)
		{
			perror("cd");
		}
		if (judge != 0)
		{
			perror("cd");
		}
	}
	return (judge);//success or fail
}