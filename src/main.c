#include "../header/standard.h"
#include "../header/condition.h"
#include "../header/lexer.h"
#include "../header/signal.h" 
#include "../header/init.h"
#include "../libft/libft.h"
#include "../header/print.h"
#include "../header/execution.h"

#include <unistd.h>

sig_atomic_t g_sig = 0;


void free_tokens(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token->next;
		printf("freed token = %s\n", token->token);
		free(token->token);
		free(token);
		token = temp;
	}
}

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

void init_condition(t_condition *condition)
{
	errno = 0;
	setup_parent_signal();
	if (g_sig != 0)
	{
		condition->exit_status = g_sig + 128;
		g_sig = 0;
	}
	(void)condition;
}

void shell_loop(t_condition *condition)
{
	char *line;
	t_token *tokenized;

	while (true)
	{
		init_condition(condition);
		line = read_command_line();
		if(!line)
			break;
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		tokenized = lexer(condition, line);
		run_command(condition, tokenized);//TOKEN_UNKNOWNが含まれている場合止めておいたほうがいい
		free(line);
	}
	return ;
}

int main(int argc, char **argv, char **envp)
{
	t_condition condition;
	t_item *temp;

	if (!init_shell(&condition, argv, envp))
		return (put_error(strerror(errno)), 1);
	shell_loop(&condition);
	/////////仮///////////
	while(condition.environ)
	{
		temp = condition.environ->next;
		free(condition.environ->key);
		free(condition.environ->value);
		free(condition.environ);
		condition.environ = temp;
	}
	rl_clear_history();
	(void)argc;
}
