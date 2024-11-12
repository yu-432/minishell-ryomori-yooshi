#include "../../libft/libft.h"

void put_tokenizer_error(char *str)
{
	ft_putstr_fd("minishell: tokenizer: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
}

void put_unexpected_token_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (ft_strlen(token) <= 3)
		ft_putchar_fd(token[0], 2);
	else
	{
		ft_putchar_fd(*token, 2);
		ft_putchar_fd(*token, 2);
	}
	ft_putstr_fd("'\n", 2);
}


void put_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: syntax error unclosed quote `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}
