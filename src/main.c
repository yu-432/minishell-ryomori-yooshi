#include "../header/condition.h"
#include "../header/standard.h"
#include "../header/lexer.h"
#include "../header/init.h"
#include "../libft/libft.h"
#include "../header/print.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#define PROMPT "minishell$ "

char *read_command_line()
{
	char *line;

	line = readline(PROMPT);
	if (!line)
		return (NULL);
	if (*line != '\0')
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
		update_condition(condition);
		line = read_command_line();
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		if(line == NULL)
			break;//minishell_exit的な関数を作成しfreeする必要がある
		lexer(condition, line);
		free(line);
	}
	return ;
}

int main(int argc, char **argv, char **envp)
{
	t_condition condition;
	t_item *temp;

	if (!init_shell(&condition, argv, envp))
	{
		put_error("initialization error");
		exit(1);
	}
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
