#include "../header/standard.h"
#include "../header/condition.h"
#include "../header/lexer.h"
#include "../header/signal.h" 
#include "../header/init.h"
#include "../libft/libft.h"
#include "../header/print.h"
#include "../header/execution.h"

sig_atomic_t g_sig = 0;

void free_tokens(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token->next;
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
			line = ft_strdup("exit");
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		tokenized = lexer(condition, line);
		run_command(condition, tokenized);
		free(line);
	}
	return ;
}

int main(int argc, char **argv, char **envp)
{
	t_condition condition;

	if (!init_shell(&condition, envp))
		return (put_error(strerror(errno)), 1);
	shell_loop(&condition);
	rl_clear_history();
	(void)argc;
	(void)argv;
	exit(condition.exit_status);
}
