/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:47 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 15:15:30 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include "../../header/print.h"

static int	count_word_len(char *line)
{
	int		count;
	char	quote;

	count = 0;
	while (line[count] && !is_metacharacter(line[count]))
	{
		if (is_quote(line[count]))
		{
			quote = line[count++];
			while (line[count] && line[count] != quote)
				count++;
			if (!line[count])
				return (count);
			count++;
		}
		else
			count++;
	}
	return (count);
}

static bool	take_meta_token(char **line, t_token *tail_token)
{
	char	*token;
	int		count;

	count = count_same_char(*line, (*line)[0]);
	token = ft_calloc(count + 1, sizeof(char));
	if (!token)
		return (put_tokenizer_error(strerror(errno)), false);
	ft_memset(token, (*line)[0], count);
	tail_token->next = new_token(token, get_token_kind(token));
	if (!tail_token->next)
	{
		free(token);
		return (put_tokenizer_error(strerror(errno)), false);
	}
	*line += count;
	return (true);
}

static bool	take_word_token(char **line, t_token *tail_token)
{
	char	*token;
	int		count;

	count = count_word_len(*line);
	token = ft_substr(*line, 0, count);
	if (!token)
		return (put_tokenizer_error(strerror(errno)), false);
	tail_token->next = new_token(token, TOKEN_WORD);
	if (!tail_token->next)
	{
		free(token);
		return (put_tokenizer_error(strerror(errno)), false);
	}
	*line += count;
	return (true);
}

t_token	*tokenizer(char *line)
{
	t_token	head;

	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			line++;
		else if (is_metacharacter(*line))
		{
			if (!take_meta_token(&line, find_tail_token(&head)))
				return (free_tokens(head.next), NULL);
		}
		else
		{
			if (!take_word_token(&line, find_tail_token(&head)))
				return (free_tokens(head.next), NULL);
		}
	}
	return (head.next);
}
