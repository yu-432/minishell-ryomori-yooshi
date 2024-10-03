#include "../header/condition.h"
#include "../header/init.h"

int init_condition(t_condition *condition, char **argv, char **envp)
{
	ft_memset(condition, 0, sizeof(t_condition));
	condition->environ = touch_environ_list(envp);
	if (!condition->environ)
		return(0);//todo
	errno = 0;
	//set environ
	//exportは自作関数のため、独自に作成したenvironに保存する
	//unsetも同様
	
	
}

int	init_shell(t_condition *condition, char **argv, char **envp)
{
	init_condition(condition, argv, envp);
}