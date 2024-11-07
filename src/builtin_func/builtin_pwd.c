#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/builtin_func.h"
#include "../../header/init.h"

int builtin_pwd(t_condition *cond, char **argv)
{
	char *pwd_path;

	pwd_path = get_item_value(cond->environ, "PWD");
	if (pwd_path == NULL)
	{
		perror("get_item_value");
		return (1);
	}
	else
	{
		write(STDOUT_FILENO, pwd_path, ft_strlen(pwd_path));
		write(STDOUT_FILENO, "\n", 1);
		return(0);
	}
	(void)argv;
}
