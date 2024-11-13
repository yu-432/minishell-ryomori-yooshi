/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:35 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 03:33:10 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/standard.h"

t_token	*lexer(t_condition *condition, char *line)
{
	t_token	*tokenized;

	tokenized = tokenizer(line);
	if (!tokenized)
		return (NULL);
	if (!find_syntax_error(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	if (!expand_token(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	return (tokenized);
}
