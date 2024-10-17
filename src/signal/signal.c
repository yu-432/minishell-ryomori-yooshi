#include "../../header/lexer.h"
#include "../../header/signal.h"
#include "../../header/condition.h"

void set_global_sig(int sig)
{
	g_sig = sig;
}

void set_shell_input_sig_handler(void)
{
	signal(SIGINT, set_global_sig);
	signal(SIGQUIT, SIG_IGN);
}

// void sig_int(int sig)
// {
// 	(void)sig;
// 	if (g_sig == 0)
// 	{
		
// 	}
// }