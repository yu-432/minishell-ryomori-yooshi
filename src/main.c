#include "../header/condition.h"
#include "../header/standard.h"
#include "../header/init.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#define PROMPT "minishell$ "
#define PATH_NAME_SIZE 1024

char *read_command_line()
{
	char *line;

	line = readline(PROMPT);
	if (!line)
	{
		printf("TODO:readline error\n");
		exit(1);
	}
	if (*line == '\0')
		add_history(line);
	return (line);
}

void update_condition(t_condition *condition)
{
	errno = 0;
	//g-signal?
	(void)condition;
}

void shell_loop(t_condition *condition)
{
	char *line;

	while (true)
	{
		update_condition(condition);//いるかわからない
		line = read_command_line();
		//TODO:tokenizer->parser
		if (*line == '\0')//仮にlineがNULLだった場合終了させる
			break ;
		free(line);
	}
	return ;
}

int main(int argc, char **argv, char **envp)
{
	t_condition condition;
	t_item *temp;

	init_shell(&condition, argv, envp);
	shell_loop(&condition);
	while(condition.environ)//仮
	{
		temp = condition.environ->next;
		free(condition.environ->key);
		free(condition.environ->value);
		free(condition.environ);
		condition.environ = temp;
	}
	(void)argc;
}
