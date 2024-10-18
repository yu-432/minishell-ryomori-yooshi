#include "../../header/lexer.h"
#include "../../header/signal.h"	
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../libft/libft.h"

void set_global_sig(int sig, siginfo_t *sig_info, void *v)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
	(void)sig_info;
	(void)v;
}

void set_shell_input_sig_handler(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = set_global_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}