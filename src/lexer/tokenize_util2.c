/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:42 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:57:43 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/token.h"

int get_token_kind(char *token)
{
	if (ft_strncmp(token, ">>", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(token, ">", 2) == 0)
		return(TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(token, "|", 2) == 0)
		return (TOKEN_PIPE);
	else
		return (TOKEN_UNKNOWN);
}

int count_same_char(char *line, char c)
{
	int count;

	count = 0;
	while(line[count] == c)
		count++;
	return (count);
}

t_token *find_tail_token(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_token *new_token(char *token, t_token_kind kind)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->kind = kind;
	return (new);
}