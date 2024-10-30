
bool char_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}




int	builtin_exit(char **args)
{
	char *argment;
	int num;

	if(args[1] == NULL)
		exit(last_command_status);//execveの返り値を返す

	if(args[2] != NULL)
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}

	argment = args[1];
	num = 0;
	if (check_is_digit(argment) == 0)
	{
		num = ft_atoi(argment);
		exit(num);
	}

}