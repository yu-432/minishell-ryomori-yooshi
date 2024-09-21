
#include "test.h"

//execve関数(関数へのフルパス、起動する関数への引数(オプション)、環境変数へのポインタ)
//第一引数にはフルパスを渡す必要がある(今試した所)のでどこかでPATHに対してコマンドを付け加えた
//フルパスを作成し、渡す必要がある
//execve関数が正常に動作した場合このプロセスは参照先のコマンドのプロセスに完全に置き換わるため、
// どこでmallocした文字列をfreeするかが問題
// 	->構造体かなにかにアドレスを保持しておく？
//親プロセスで有効なパスをaccess関数で検索しておいて存在すればforkして子プロセスでexecveする
//子プロセスが終了次第親プロセスでfreeする
// access関数を用いることでファイルの確認をすることが可能だが、する必要性が特にないため書いていない
// cc execve.c libft/ft_split.c libft/ft_memcpy.c libft/ft_strjoin.c libft/ft_strlen.c -lreadline -lhistory

// unset PATH

// 1. t_item (structure - linked list)
// name
// value
// *next

// 2. t_map (structure)
// {
// t_item *item
// extern char **environ
// }

// extern sig_atomic g_signal;

char	*find_command(char *line)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", line);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
			return (free(path), joined);
		free(joined);
		i++;
	}
	free(path);
	return (NULL);
}

int	interpret(char *line, char **argv)
{
	extern char	**environ;
	char		*absolute_path;
	pid_t		pid;
	int			waitstat;

	absolute_path = find_command(line);
	pid = fork();
	if (pid < 0)
	{
		printf("fork error\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child active\n");
		if (absolute_path)
			execve(absolute_path, argv, environ);
		else
			printf("Command not found\n");
		exit(0);
	}
	if (pid > 0)
	{
		wait(&waitstat);
		free(absolute_path);
		return (printf("wait status = %d\n", waitstat), 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token *token;
	

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("Rreadline error\n");
			break ;
		}

		if (ft_strlen(line) == 0)//テスト用SIGINTが入力された場合の処理を仮定
		{
			free(line);
			break ;
		}
		token = tokenize(line);//トークン化Lexer
		
		// if (*line != '\0')
		// 	add_history(line);
		// free(line);
		while(token->next)
		{
			t_token *temp;
			printf("token freed[%s]\n", token->token);
			if (token->next)
				temp = token->next;
				free(token->token);
			free(token);
			token = temp;
		}
		free(token->token);
		free(token);
		printf("-------------------------------------------------\n");
	}
	rl_clear_history();
	printf("exit\n");
}