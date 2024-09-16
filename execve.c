#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

// cc execve.c libft/ft_split.c libft/ft_memcpy.c -lreadline -lhistory



int interpret(char *line, char **argv)
{
	// extern char **environ;
	char **path;
	char *joined;
	char *adsl;
	pid_t pid;
	int waitstat;

	pid = fork();
	if (pid < 0)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// printf("getenv %s\n", getenv("PATH"));
		path = ft_split(getenv("PATH"), ':');
		// for(int i = 0; path[i] != NULL; i++)
		// 	printf("path = %s\n", path[i]);
		printf("child active\n");
		for(int i = 0; path[i] != NULL; i++)
		{
			adsl = ft_strjoin("/", line);
			joined = ft_strjoin(path[i], adsl);
			free(adsl);
			execve(joined, argv, path);
			free(joined);
		}
		printf("test\n");
		exit(EXIT_SUCCESS);
	}
	if (pid > 0)
	{
		wait(&waitstat);
		return(printf("wait status = %d\n", waitstat), 0);
	}
	return(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("Rreadline error\n");
			break ;
		}
		interpret(line, argv);
		if (*line != '\0')
			add_history(line);
		free(line);
	}
	printf("exit\n");
}