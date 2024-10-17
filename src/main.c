#include "../header/standard.h"
#include "../header/condition.h"
#include "../header/lexer.h"
#include "../header/signal.h" 
#include "../header/init.h"
#include "../libft/libft.h"
#include "../header/print.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#define PROMPT "minishell$ "
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

void update_condition(t_condition *condition)
{
	errno = 0;
	set_shell_input_sig_handler();
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

	signal(SIGINT, SIG_IGN);
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
		tokenized = lexer(condition, line);
		free(line);
		if (!tokenized)
			free_tokens(tokenized);
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
	(void)argc;
}
