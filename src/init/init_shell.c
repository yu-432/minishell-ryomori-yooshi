#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../header/environ.h"
#include "../../header/init.h"
#include "../../libft/libft.h"


void free_environ(t_item *environ)
{
	t_item *temp;

	if (!environ)
		return;
	while (environ)
	{
		temp = environ->next;
		free(environ->key);
		free(environ->value);
		free(environ);
		environ = temp;
	}
}

bool init_environ(t_condition *condition, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(!add_env(condition, envp[i]))
		{
			free_environ(condition->environ);
			return(false);
		}
		i++;
	}
	return(true);
}

bool first_init_condition(t_condition *condition, char **argv, char **envp)
{
	ft_memset(condition, 0, sizeof(t_condition));
	errno = 0;
	if (!init_environ(condition, envp))
		return(false);
	(void)argv;
	return(true);
}

bool	init_shell(t_condition *condition, char **argv, char **envp)
{
	if (!first_init_condition(condition, argv, envp))
		return(false);
	rl_event_hook = NULL;
	return(true);
}