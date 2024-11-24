/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:13 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/24 21:26:58 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

char	*get_line(int fd, int *read_status)
{
	char	buf;
	char	*result;
	int		read_size;

	buf = 0;
	result = ft_strdup("");
	while (true)
	{
		if (g_sig == SIGINT)
			return (free(result), NULL);
		read_size = read(fd, &buf, 1);
		if (read_size == 0 && !ft_strlen(result))
		{
			write(STDERR_FILENO, "\n", 1);
			*read_status = INPUT_EOF;
			return (result);
		}
		if (buf == '\n')
			break ;
		if (!append_char(&result, buf))
			return (NULL);
	}
	return (result);
}

bool	expand_heredoc_dollar(t_condition *condition, char **line)
{
	int		i;
	char	*new;

	new = ft_strdup("");
	if (!new)
		return (false);
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			if (!handle_dollar(condition, *line, &new, &i))
				return (false);
		}
		else
		{
			if (!append_char(&new, (*line)[i]))
				return (false);
			i++;
		}
	}
	free(*line);
	*line = new;
	return (true);
}

void	heredoc_free_exit(char *line, int fd, int exit_status)
{
	free(line);
	wrap_close(fd);
	if (exit_status != -1)
		exit(exit_status);
}

bool	expand_quote(char **delimiter)
{
	t_expand	info;
	bool		is_expand;

	if (!init_expand_info(&info))
		exit(EXIT_FAILURE);
	is_expand = true;
	while ((*delimiter)[info.index])
	{
		if (is_quote((*delimiter)[info.index]) && info.quote == '\0')
		{
			info.quote = (*delimiter)[info.index];
			is_expand = false;
		}
		else if (info.quote == (*delimiter)[info.index])
			info.quote = '\0';
		else
			append_char(&info.new, (*delimiter)[info.index]);
		info.index++;
	}
	free(*delimiter);
	*delimiter = info.new;
	return (is_expand);
}
