#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/condition.h"
#include "../../header/environ.h"
#include <sys/stat.h>//add(ryomori):builtin_pwd

int builtin_pwd(char *line, t_condition *cond)
{
	char pwd_path[PATH_MAX];

	(void)line;
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
}
