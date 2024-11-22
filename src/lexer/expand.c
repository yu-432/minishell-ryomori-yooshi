/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:26 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/22 20:36:02 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"

bool	append_char(char **str, char c)
{
	char	*new;
	char	join[2];

	join[0] = c;
	join[1] = '\0';
	new = ft_strjoin(*str, join);
	if (!new)
		return (false);
	free(*str);
	*str = new;
	return (true);
}

static bool	update_quote_status(t_expand *expand_info , char *str)
{
	if (expand_info->quote == '\0')
	{
		expand_info->quote = str[expand_info->index];
		return (true);
	}
	else if (expand_info->quote == str[expand_info->index])
	{
		expand_info->quote = '\0';
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

// bool	expand_token(t_condition *condition, t_token *tokenized)
// {
// 	int		i;
// 	char	quote;
// 	char	*new;

// 	while (tokenized)
// 	{
// 		if (tokenized->kind == TOKEN_WORD)
// 		{
// 			quote = '\0';
// 			new = ft_strdup("");
// 			i = 0;
// 			while (tokenized->token[i])
// 			{
// 				if (is_quote(tokenized->token[i]) && \
// 						update_quote_status(&quote, tokenized->token[i]))
// 					i++;
// 				else if (quote != SINGLE_QUOTE && tokenized->token[i] == '$' && \
// 							count_envname_len(tokenized->token, i + 1))
// 					handle_dollar(condition, tokenized->token, &new, &i);
// 				else
// 					append_char(&new, tokenized->token[i++]);
// 			}
// 			free(tokenized->token);
// 			tokenized->token = new;
// 		}
// 		tokenized = tokenized->next;
// 	}
// 	return (true);
// }

bool init_expand_info(t_expand *expand_info)
{
	expand_info->new = ft_strdup("");
	if (!expand_info->new)
		return (false);
	expand_info->index = 0;
	expand_info->quote = '\0';
	return (true);
}

bool expand_single_token(t_condition *condition, t_token *tokenized)
{
	t_expand expand_info;

	if(!init_expand_info(&expand_info))
		return (false);
	while(tokenized->token[expand_info.index])
	{
		if (is_quote(tokenized->token[expand_info.index]) && \
				update_quote_status(&expand_info, tokenized->token))
			expand_info.index++;
		else if (expand_info.quote != SINGLE_QUOTE && tokenized->token[expand_info.index] == '$' && \
					count_envname_len(tokenized->token, expand_info.index + 1))
			handle_dollar(condition, tokenized->token, &expand_info.new, &expand_info.index);
		else if(!append_char(&expand_info.new, tokenized->token[expand_info.index++]))
			return (false);
	}
	free(tokenized->token);
	tokenized->token = expand_info.new;
	return (true);
}

bool expand_token(t_condition *condition, t_token *tokenized)
{
	bool success;

	success = true;
	while(tokenized && success)
	{
		if(tokenized->kind == TOKEN_WORD)
			success = expand_single_token(condition, tokenized);
		tokenized = tokenized->next;
	}
	return (true);
}
