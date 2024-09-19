/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:58 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/19 17:50:48 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// cc execve.c tokenizer.c libft.a test.h -lreadline -lhistory


t_token	*new_token(char *word, t_token_kind kind)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = word;
	new->kind = kind;
	new->next = NULL;
	return (new);
}

void add_token(t_token *list, t_token *new)
{

	if (!list)
		return ;
	while (list->next)
		list = list->next;
	list->next = new;
}

bool is_operator(char *line)
{
	char *op[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "|&", "\n", NULL};
	int i;

	i = 0;
	while (op[i])
	{
		if (!ft_strncmp(line, op[i], ft_strlen(op[i])))
			return (true);
		i++;
	}
	return (false);
}

bool is_redirection(char c)
{
	return (c && (c == '>' || c == '<'));
}

bool is_metacharacter(char c)
{
	// printf("c = %c\n", c);
	return (c  && ft_strchr("|&;()<> \t\n\0", c));
}

bool is_space(char c)
{
	return (c == ' ' || c == '\t');
}

bool is_word(char c)
{
	return (c && !is_metacharacter(c));
}

bool is_quote(char c)
{
	return (c && (c == '\'' || c == '\"'));
}

int op_len(char *line)
{
	int i;

	i = 0;
	while (line[i] && !is_space(line[i]))
		i++;
	return (i);
}

t_token *op_token(char **line, t_token *head)
{
	int len;
	char *operation;
	t_token *new;

	operation = ft_substr(*line, 0, op_len(*line));
	if (!operation)
		return (NULL);
	len = ft_strlen(operation);
	*line += len;
	new = new_token(operation, TOKEN_OPE);
	add_token(head, new);
	return (new);//sample
}

t_token *word_token(char **line , t_token *head)
{
	int i;
	char *word;
	char quote;
	int quote_count;
	t_token *new;

	i = 0;
	quote_count = 0;
	quote = '\0';
	while ((*line)[i] && (quote || !is_metacharacter((*line)[i])))
	{
		if (quote == (*line)[i] && is_metacharacter((*line)[i + 1]))
		{
			i++;
			break ;
		}
		if (is_quote((*line)[i]) && quote == '\0')
			quote = (*line)[i];
		else if (quote == (*line)[i])
			quote = '\0';
		i++;
	}
		// printf("word token %s\n", *line);
	word = ft_substr(*line, 0, i);
	if (!word)
		return (NULL);
	*line += i;
	new = new_token(word, TOKEN_WORD);
	add_token(head, new);
	return (new);//sample
}

t_token *metacharacter_token(char **line, t_token *head)
{
	int i;
	char *redirection;
	t_token *new;

	i = 0;
	while ((*line)[i] && is_metacharacter((*line)[i]))
		i++;
	redirection = ft_substr(*line, 0, i);
	if (!redirection)
		return (NULL);
	*line += i;
	new = new_token(redirection, TOKEN_REDIRECT);
	add_token(head, new);
	return (new);//sample
}

t_token *tokenize(char *line)
{
	t_token head;

	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			line++;
		else if(is_metacharacter(*line))
			metacharacter_token(&line, &head);
		else if (is_operator(line))
			op_token(&line, &head);
		else if (is_word(*line))
			word_token(&line, &head);
		else
		{
			printf("error\n");
			break;
		}
	}
	add_token(&head, new_token(NULL, TOKEN_EOF));//いる？
	return (head.next);
}

