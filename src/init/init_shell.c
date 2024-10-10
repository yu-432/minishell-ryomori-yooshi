#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../header/init.h"
#include "../../libft/libft.h"


bool init_environ(t_condition *condition, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		// printf("%s\n", envp[i]);
		if(!add_eenv(condition, envp[i]))
		{
			//TODO:エラー処理
			return(false);
		}
		i++;
	}
	return(true);
}

int init_condition(t_condition *condition, char **argv, char **envp)
{
	ft_memset(condition, 0, sizeof(t_condition));
	errno = 0;
	init_environ(condition, envp);
	//TODO:exportは自作関数のため、独自に作成したenvironに保存する
	//unsetも同様
	// condition->cwd = getenv("PWD");//必要？
	(void)argv;
	return(0);
}

int	init_shell(t_condition *condition, char **argv, char **envp)
{
	init_condition(condition, argv, envp);
	return(0);
}