/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:26 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/24 17:25:34 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"

static bool	update_quote_status(t_expand *info, char *str)
{
	if (info->quote == '\0')
	{
		info->quote = str[info->index];
		return (true);
	}
	else if (info->quote == str[info->index])
	{
		info->quote = '\0';
		return (true);
	}
	else
		return (false);
}

static int	count_envname_len(char *token, int i)
{
	int	len;

	len = 0;
	if (token[i] == '?')
		len++;
	else
		while (token[i] && (ft_isalnum(token[i + len]) || \
					token[i + len] == '_'))
			len++;
	return (len);
}

bool	init_expand_info(t_expand *info)
{
	info->new = ft_strdup("");
	if (!info->new)
		return (false);
	info->index = 0;
	info->quote = '\0';
	return (true);
}

bool	expand_single_token(t_condition *condition, t_token *tokenized)
{
	t_expand	info;

	if (!init_expand_info(&info))
		return (false);
	while (tokenized->token[info.index])
	{
		if (is_quote(tokenized->token[info.index]) && \
				update_quote_status(&info, tokenized->token))
			info.index++;
		else if (info.quote != SINGLE_QUOTE && \
				tokenized->token[info.index] == '$' && \
				count_envname_len(tokenized->token, info.index + 1))
			handle_dollar(condition, tokenized->token, &info.new, &info.index);
		else if (!append_char(&info.new, tokenized->token[info.index++]))
			return (false);
	}
	free(tokenized->token);
	tokenized->token = info.new;
	return (true);
}

bool	expand_token(t_condition *condition, t_token *tokenized)
{
	bool			success;
	t_token_kind	prev_kind;

	success = true;
	prev_kind = TOKEN_WORD;
	while (tokenized && success)
	{
		if (tokenized->kind == TOKEN_WORD && \
				prev_kind != TOKEN_REDIRECT_HEREDOC)
			success = expand_single_token(condition, tokenized);
		prev_kind = tokenized->kind;
		tokenized = tokenized->next;
	}
	if (!success)
		return (false);
	return (true);
}
