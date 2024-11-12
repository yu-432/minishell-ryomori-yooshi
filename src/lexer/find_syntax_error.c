/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_syntax_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:29 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:57:33 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../header/condition.h"
#include "../../libft/libft.h"
#include "../../header/print.h"

bool check_quote_error(char *token)
{
	int i;
	char quote;

	i = 0;
	while (token[i])
	{
		if (is_quote(token[i]))
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				i++;
			if (token[i] != quote)
				return(put_unclosed_quote_error(quote), false);
			i++;
		}
		else
			i++;
	}
	return (true);
}


bool check_token_kind(t_token_kind kind, t_token *token)
{
	if (!(kind == TOKEN_WORD \
		|| kind == TOKEN_PIPE \
		|| kind == TOKEN_REDIRECT_IN \
		|| kind == TOKEN_REDIRECT_OUT \
		|| kind == TOKEN_REDIRECT_APPEND \
		|| kind == TOKEN_REDIRECT_HEREDOC \
		|| kind == TOKEN_EOF))
			return (put_unexpected_token_error(token->token), false);
	return (true);
}

bool check_pipe_error(t_token_kind kind, t_token *token, t_token_kind prev_kind)
{
	if ((prev_kind == TOKEN_PIPE && kind == TOKEN_PIPE) || \
		(kind == TOKEN_PIPE && !token->next))
		return (put_unexpected_token_error(token->token), false);
	return (true);
}

bool find_syntax_error(t_condition *condition, t_token *tokenized)
{
	t_token_kind prev_kind;

	prev_kind = TOKEN_PIPE;
	while (tokenized)
	{
		if (!check_token_kind(tokenized->kind, tokenized))
			return (false);
		if (!check_pipe_error(tokenized->kind, tokenized, prev_kind))
			return (false);
		if (!check_quote_error(tokenized->token))
			return (false);
		prev_kind = tokenized->kind;
		tokenized = tokenized->next;
	}
	(void)condition;
	return (true);
}
