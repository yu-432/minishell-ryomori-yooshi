#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

//execve関数(関数へのフルパス、起動する関数への引数(オプション)、環境変数へのポインタ)
//第一引数にはフルパスを渡す必要がある(今試した所)のでどこかでPATHに対してコマンドを付け加えた
//フルパスを作成し、渡す必要がある
//execve関数が正常に動作した場合このプロセスは参照先のコマンドのプロセスに完全に置き換わるため、
// どこでmallocした文字列をfreeするかが問題
// 	->構造体かなにかにアドレスを保持しておく？
// access関数を用いることでファイルの確認をすることが可能だが、する必要性が特にないため書いていない

// cc execve.c libft/ft_split.c libft/ft_memcpy.c libft/ft_strjoin.c libft/ft_strlen.c -lreadline -lhistory

int interpret(char *line, char **argv)
{
	extern char **environ;
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
		path = ft_split(getenv("PATH"), ':');
		printf("child active\n");
		for(int i = 0; path[i] != NULL; i++)
		{
			adsl = ft_strjoin("/", line);
			joined = ft_strjoin(path[i], adsl);
			free(adsl);
			execve(joined, argv, environ);
			printf("invalid path\n");
			free(joined);
		}
		printf("command not found\n");
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