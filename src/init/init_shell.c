#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../header/init.h"
#include "../../libft/libft.h"


int init_environ(t_condition *condition, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		add_env(condition, envp[i]);//condition->environにtouch t itemにinitしたnullが含まれている、が、問題ないので一旦放置
		i++;
	}
	return(0);
}

int init_condition(t_condition *condition, char **argv, char **envp)
{
	ft_memset(condition, 0, sizeof(t_condition));
	condition->environ = touch_t_item();
	if (!condition->environ)
	{
		printf("TODO:touch_environ_list failed\n");
		return (1);
	}
	errno = 0;
	init_environ(condition, envp);
	//exportは自作関数のため、独自に作成したenvironに保存する
	//unsetも同様
	(void)argv;
	return(0);
}

int	init_shell(t_condition *condition, char **argv, char **envp)
{
	init_condition(condition, argv, envp);
	return(0);
}