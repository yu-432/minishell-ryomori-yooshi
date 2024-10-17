#include "../../libft/libft.h"

void put_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void put_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}
