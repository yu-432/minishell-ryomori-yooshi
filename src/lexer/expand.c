/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:26 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 14:09:18 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/token.h"
#include "../../header/lexer.h"
#include "../../libft/libft.h"

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

bool	expand_token(t_condition *condition, t_token *tokenized)
{
	while (tokenized)
	{
		if (tokenized->kind == TOKEN_WORD)
		{
			if (!expand_dollar(condition, tokenized))
				return (false);
			if (!expand_quote(tokenized))
				return (false);
		}
		tokenized = tokenized->next;
	}
	return (true);
}
