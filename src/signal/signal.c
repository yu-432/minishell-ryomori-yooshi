#include "../../header/lexer.h"
#include "../../header/signal.h"	
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../libft/libft.h"

void set_global_sig(int sig)
{
	g_sig = sig;
	if (g_foreground_pid != 0)
		kill(g_foreground_pid, SIGINT);
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
	}
}

void set_shell_input_sig_handler(void)
{
	signal(SIGINT, set_global_sig);
	signal(SIGQUIT, SIG_IGN);
}