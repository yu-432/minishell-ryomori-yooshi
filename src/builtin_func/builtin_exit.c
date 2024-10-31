#include "../../header/condition.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"

bool is_check_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(char **args, t_condition *condition)
{
	char *argment;
	int num;

	if(args[1] == NULL)
		exit(condition->exit_status);//execveの返り値を返す

	if(args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}

	argment = args[1];
	num = 0;
	if (is_check_num(argment))
	{
		num = ft_atoi(argment);
		exit(num);
	}
	
	fprintf(stderr, "exit: %s: numeric argument required\n", argment);
	exit(255);
}