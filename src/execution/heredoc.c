#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"

bool heredoc_strjoin(char **heredoc_str, char *line)
{
	char *temp;

	temp = ft_strjoin(*heredoc_str, line);
	if (!temp)
		return (false);
	free(*heredoc_str);
	*heredoc_str = NULL;
	*heredoc_str = ft_strjoin(temp, "\n");
	if (!heredoc_str)
		return (free(temp), false);
	return (true);
}

bool redirect_heredoc(t_node *node, int i)
{
	char *line;

	free(node->heredoc_str);
	node->heredoc_str = ft_strdup("");
	if (!node->heredoc_str)
		return (false);
	if (!node->argv[i + 1])
	{
		put_error("syntax error near unexpected token `newline'");
		return (false);
	}
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (false);
		if (!ft_strncmp(line, node->argv[i + 1], ft_strlen(node->argv[i + 1])))
		{
			free(line);
			break;
		}
		heredoc_strjoin(&node->heredoc_str, line);
		free(line);
	}
	return (true);
}
