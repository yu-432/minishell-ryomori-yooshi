#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"

bool is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "echo", 5) == 0 || \
		ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "pwd", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 6) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0 || \
		ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

bool is_not_redirect(char *str)
{
	int kind;

	kind = get_token_kind(str);
	if (kind == TOKEN_REDIRECT_IN || kind == TOKEN_REDIRECT_OUT ||\
		kind == TOKEN_REDIRECT_APPEND || kind == TOKEN_REDIRECT_HEREDOC)
		return (false);
	return (true);
}

int count_cmd_arg(t_node *node)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (node->argv[i])
	{
		if (is_not_redirect(node->argv[i]))
			count++;
		else
			count--;
		i++;
	}
	return (count);
}

char *take_env_value(t_condition *condition, char *key)
{
	t_item *current;

	current = condition->environ;
	while (current)
	{
		if (!ft_strncmp(current->key, key, strlen(key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*find_command_path(t_condition *condition, char *command)
{
	int		i;
	char	**path;
	char	*slash;
	char	*joined;

	path = ft_split(take_env_value(condition, "PATH"), ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin("/", command);
		joined = ft_strjoin(path[i], slash);
		free(slash);
		if (!access(joined, F_OK))
			return (free(path), joined);
		free(joined);
		i++;
	}
	free(path);
	return (NULL);
}
