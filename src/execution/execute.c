/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:56 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 00:53:41 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"
#include "../../header/signal.h"

void	execute_builtin(t_condition *condition, t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		builtin_echo(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		builtin_export(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		builtin_unset(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		builtin_env(condition);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		builtin_cd(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		builtin_pwd(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		builtin_exit(condition, node->argv);
	else
		ft_putstr_fd("error: builtin command not found\n", STDERR_FILENO);
}

static bool	convert_list_to_array(t_item *environ, char **ft_envp)
{
	int	i;

	i = 0;
	while (environ)
	{
		ft_envp[i] = ft_strjoin(environ->key, "=");
		if (!ft_envp[i])
			return (false);
		ft_envp[i] = ft_strjoin(ft_envp[i], environ->value);
		if (!ft_envp[i])
			return (false);
		environ = environ->next;
		i++;
	}
	ft_envp[i] = NULL;
	return (true);
}

static bool	make_envp(t_condition *condition)
{
	int	item_count;

	item_count = count_environ(condition->environ);
	condition->envp = ft_calloc(item_count + 1, sizeof(char *));
	if (!condition->envp)
		return (false);
	if (!convert_list_to_array(condition->environ, condition->envp))
		return (false);
	return (true);
}

static void	path_check(t_node *node, char *path)
{
	if (!path)
	{
		ft_putstr_fd(node->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->argv[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit (127);
	}
	if (!is_executable(path))
		exit (126);
	if (path[0] == '\0')
		exit(EXIT_SUCCESS);
}

int	execute(t_condition *condition, t_node *node)
{
	char	*path;

	if (!interpret_redirect(condition, node))
		exit(EXIT_FAILURE);
	set_redirect_fd(node);
	make_envp(condition);
	if (is_builtin(node->argv[0]))
	{
		execute_builtin(condition, node);
		exit (EXIT_SUCCESS);
	}
	if (is_path(node->argv[0]))
		path = ft_strdup(node->argv[0]);
	else
		path = find_command_path(condition, node->argv[0]);
	path_check(node, path);
	execve(path, node->argv, condition->envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->argv[0], STDERR_FILENO);
	perror(": ");
	exit(126);
}
