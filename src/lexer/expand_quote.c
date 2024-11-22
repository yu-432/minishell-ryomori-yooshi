/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:22 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/22 19:26:10 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../header/lexer.h"

// bool	expand_quote(t_token *tokenized)
// {
// 	int		i;
// 	char	quote;
// 	char	*new;

// 	i = 0;
// 	quote = 0;
// 	new = ft_strdup("");
// 	if (!new)
// 		return (false);
// 	while (tokenized->kind == TOKEN_WORD && tokenized->token[i])
// 	{
// 		if (is_quote(tokenized->token[i]) && quote == 0)
// 			quote = tokenized->token[i++];
// 		else if (tokenized->token[i] == quote)
// 		{
// 			quote = 0;
// 			i++;
// 		}
// 		else
// 			if (!append_char(&new, tokenized->token[i++]))
// 				return (false);
// 	}
// 	free(tokenized->token);
// 	tokenized->token = new;
// 	return (true);
// }
