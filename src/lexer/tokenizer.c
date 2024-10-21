#include "../../header/lexer.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include <string.h>

int get_token_kind(char *token)
{
	if (ft_strncmp(token, ">>\0", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(token, ">\0", 2) == 0)
		return(TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "<<\0", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else if (ft_strncmp(token, "<\0", 2) == 0)
		return (TOKEN_REDIRECT_IN);
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

bool take_meta_token(char **line, t_token *tail_token)
{
	char *token;
	int count;

	count = count_same_char(*line, (*line)[0]);
	token = ft_calloc(count + 1, sizeof(char));
	if (!token)
		return (put_error(strerror(errno)), false);
	ft_memset(token, (*line)[0], count);
	tail_token->next = new_token(token, get_token_kind(token));
	if (!tail_token->next)
		return (put_error(strerror(errno)), false);
	*line += count;
	return (true);
}

int count_word_len(char *line)
{
	int count;
	char quote;

	count = 0;
	while (line[count] && !is_metacharacter(line[count]))
	{
		if (is_quote(line[count]))
		{
			quote = line[count++];
			while (line[count] && line[count] != quote)
				count++;
			count++;
		}
		else
			count++;
	}
	return (count);
}

bool take_word_token(char **line, t_token *tail_token)
{
	char *token;
	int count;

	count = 0;
	count = count_word_len(*line);
	token = ft_substr(*line, 0, count);
	if (!token)
		return (put_error(strerror(errno)), false);
	tail_token->next = new_token(token, TOKEN_WORD);
	if (!tail_token->next)
		return(put_error(strerror(errno)), false);
	*line += count;
	return (true);
}

t_token *tokenizer(char *line)
{
	t_token head;
	bool meta_ret;
	bool word_ret;

	meta_ret = true;
	word_ret = true;
	ft_memset(&head, 0, sizeof(t_token));
	while (*line)
	{
		if (is_space(*line))
			line++;
		else if (is_metacharacter(*line))
			meta_ret = take_meta_token(&line, find_tail_token(&head));
		else
			word_ret = take_word_token(&line, find_tail_token(&head));
		if (!meta_ret || !word_ret)
		{
			free_tokens(head.next);
			return (NULL);
		}
	}
	return(head.next);
}