#include "../../header/lexer.h"
#include "../../header/signal.h"	
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../libft/libft.h"
#include <sys/ioctl.h>

void handler(int signum)
{
	if(signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = signum;
	}
}

void heredoc_handler(int signum)
{
	if(signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_sig = signum;
		exit(SIGINT);
	}
}

void init_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	ioctl(STDIN_FILENO, TIOCSTI, "\0");
}

void setup_ignore_signal(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void setup_heredoc_signal(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = heredoc_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void setup_parent_signal(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void setup_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
