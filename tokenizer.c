/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:58 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/26 11:11:32 by yooshima         ###   ########.fr       */
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
	char *op[] = {"&&", "&", ";;", ";", "(", ")", "||", "|&", "|", "\n", NULL};
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
	char *op[] = {"&&", "&", ";;", ";", "(", ")", "||", "|&", "|", "\n", NULL};
	int i;
	int len;

	while (op[i])
	{
		len = ft_strlen(op[i]);
		if (!ft_strncmp(line, op[i], len))
			return (len);
		i++;
	}
	return (0);
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
	t_token *new;

	i = 0;
	while ((*line)[i] && !is_metacharacter((*line)[i]))
	{
		if ((*line)[i] == '\'')
		{
			i++;
			while ((*line)[i] != '\'')
			{
				if ((*line)[i] == '\0')
				{
					printf("unclosed quote error\n");
					exit(1);
				}
				i++;
			}
			i++;
		}
		else if ((*line)[i] == '\"')
		{
			i++;
			while ((*line)[i] != '\"')
			{
				if ((*line)[i] == '\0')
				{
					printf("unclosed quote error\n");
					exit(1);
				}
				i++;
			}
			i++;
		}
		else
			i++;
	}
	printf("i = %d\n", i);
	word = ft_substr(*line, 0, i);
	printf("word = %s\n", word);
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
	new = new_token(redirection, TOKEN_META);
	add_token(head, new);
	return (new);//sample
}

t_token *tokenize(char *line)
{
	t_token	head;

	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			line++;
		// else if (is_metacharacter(*line))
		// 	metacharacter_token(&line, &head);
		else if (is_operator(line))
			op_token(&line, &head);
		else if (is_word(*line))
			word_token(&line, &head);
		else
		{
			printf("error line++\n");
			line++;
		}
	}
	add_token(&head, new_token(NULL, TOKEN_EOF));//いる？
	return (head.next);
}
// parser 
// simple command
// connection commad-> pipe