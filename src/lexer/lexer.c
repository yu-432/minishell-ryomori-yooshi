/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:35 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/22 18:26:39 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"

t_token	*lexer(t_condition *condition, char *line)
{
	t_token	*tokenized;

	tokenized = tokenizer(line);
	if (!tokenized)
		return (NULL);
	if (!find_syntax_error(tokenized))
	{
		condition->exit_status = 2;
		return (free_tokens(tokenized), NULL);
	}
	if (!expand_token(condition, tokenized))
		return (free_tokens(tokenized), NULL);
	return (tokenized);
}
