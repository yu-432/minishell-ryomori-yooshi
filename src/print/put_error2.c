/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:55 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:13:14 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/print.h"

void	put_tokenizer_error(char *str)
{
	ft_putstr_fd("minishell: tokenizer: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
}

void	put_unexpected_token_error(char *token)
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

void	put_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: syntax error unclosed quote `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}

void	put_heredoc_warning(char *delimiter)
{
	ft_putstr_fd("warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	put_redirect_error(t_condition *condition, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
	condition->exit_status = EXIT_FAILURE;
}
