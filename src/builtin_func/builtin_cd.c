#include "../../header/condition.h"
#include "../../header/standard.h"

//=============================================================================
//==========================        PROTOTYPE        ===========================
//=============================================================================

typedef enum e_move_position
{
	MOVE_TO_HOME,
	MOVE_TO_OLDPWD
}	t_move_position;

//=============================================================================
//==========================        UPDATE_OLD_PWD        =======================
//=============================================================================

static int update_old_pwd(t_condition *cond)
{
	char cwd[PATH_MAX];
	t_item *item;
	t_item *old_item;

	item = cond->environ;
	cwd = get_item_value(cond->environ, "PWD");
	while(item)
	{
		if(ft_strcmp(item->key, "OLDPWD") == 0)
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
}
//=============================================================================
//==========================        GET_ITEM_VALUE        =======================
//=============================================================================

static char *get_item_value(t_item *item, char *key)
{
	char *value;

	while(item)
	{
		if(ft_strcmp(item->key, key) == 0)
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

	if(option == MOVE_TO_HOME)
	{
		update_old_pwd(&cond);
		env_path = get_item_value(cond.environ, "HOME");
	}
	else if(option == MOVE_TO_OLDPWD)
		env_path = get_item_value(cond.environ, "OLDPWD");
	if(!env_path)
	{
		perror("get_item_value");
		return (1);
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
		return(move_path(MOVE_TO_HOME, *cond));
	if (ft_strcmp(args[1] == '-') == 0)
		judge = move_path(MOVE_TO_OLDPWD, *cond);
	else
	{
		update_old_pwd(cond);
		judge = chdir(args[1]);
		if(judge < 0)
			perror("cd");
	}
	return (judge);//success or fail
}