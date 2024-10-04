#include "../../header/condition.h"
#include "../../header/environ.h"
#include "../../header/init.h"
#include "../../libft/libft.h"


int init_environ(t_condition *condition, char **envp)
{
	printf("%s\n", envp[0]);
	add_env();
	return(0);
}

int init_condition(t_condition *condition, char **argv, char **envp)
{
	// ft_memset(condition, 0, sizeof(t_condition));
	// condition->environ = touch_environ_list(envp);
	// if (!condition->environ)
		// return(0);//todo
	// errno = 0;
	init_environ(condition, envp);
	//set environ
	//exportは自作関数のため、独自に作成したenvironに保存する
	//unsetも同様
	printf("init_shell\n");
	return(0);
}

int	init_shell(t_condition *condition, char **argv, char **envp)
{
	init_condition(condition, argv, envp);
	return(0);
}