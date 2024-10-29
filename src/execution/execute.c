#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/node.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"

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

char **molding_argv(t_node *node)
{
	char **res;
	int count;
	int i;
	int j;

	count = count_cmd_arg(node);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (is_not_redirect(node->argv[j]))
			res[i++] = node->argv[j];
		else
			j++;
		j++;
	}
	return (res);
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

bool execute(t_condition *condition, t_node *node)
{
	char **argv;
	char *path;

	argv = molding_argv(node);
	if (!argv)
		return (false);
	// if (is_builtin(argv[0]))
	// 	execute_builtin(condition, argv);
	path = find_command_path(condition, argv[0]);
	if (!path)
	{
		put_error("command not found");
		return (false);
	}
	if (execve(path, argv, NULL) == -1)
	{
		perror(strerror(errno));
		return (false);
	}
	exit(EXIT_FAILURE);
}
