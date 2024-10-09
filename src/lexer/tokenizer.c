#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"

int get_token_kind(char *token)
{
	if (ft_strncmp(token, ">>\0", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(token, ">\0", 2) == 0)
		return(TOKEN_REDIRECT_IN);
	else if (ft_strncmp(token, "<<\0", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else if (ft_strncmp(token, "<\0", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "&&\0", 3) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(token, "||\0", 3) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(token, "(\0", 2) == 0)
		return (TOKEN_LPARENT);
	else if (ft_strncmp(token, ")\0", 2) == 0)
		return (TOKEN_RPARENT);
	else if (ft_strncmp(token, "|\0", 2) == 0)
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

void meta_token(char **line, t_token *tail_token)
{
	char *token;
	int count;

	count = count_same_char(*line, (*line)[0]);
	token = ft_calloc(count + 1, sizeof(char));
	if (!token)
	{
		printf("TODO:meta_token malloc failed\n");
		exit(1);
	}
	ft_memset(token, (*line)[0], count);
	tail_token->next = new_token(token, get_token_kind(token));
	if (!tail_token->next)
	{
		printf("TODO:meta_token new_token failed\n");
		exit(1);
	}
	if (tail_token->next->kind == TOKEN_UNKNOWN)
	{
		printf("TODO:UNKNOWN TOKEN must be handled\n");
	}
	*line += count;
}

void word_token(char **line, t_token *tail_token)
{
	char *token;
	char quote;
	int count;

	count = 0;
	quote = 0;
	while ((*line)[count] && !is_metacharacter((*line)[count]))
	{
		if ((*line)[count] == '\'' || (*line)[count] =='\"')
		{
			quote = (*line)[count];
			count++;
			while ((*line)[count] && (*line)[count] != quote)
				count++;
			count++;
		}
		else
			count++;
	}
	token = ft_substr(*line, 0, count);
	if (!token)
	{
		printf("TODO:word_token substr failed\n");
		exit(1);
	}
	tail_token->next = new_token(token, TOKEN_WORD);
	if (!tail_token->next)
	{
		printf("TODO:word_token new_token failed\n");
		exit(1);
	}
	*line += count;
}

t_token *tokenizer(char *line)
{
	t_token head;

	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			line++;
		else if (is_metacharacter(*line))
			meta_token(&line, find_tail_token(&head));
		else
			word_token(&line, find_tail_token(&head));
	}
	return(head.next);
}