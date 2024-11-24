/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:56 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/24 17:17:23 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

void	execute_builtin(t_condition *condition, t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		builtin_echo(node->argv);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		builtin_export(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		builtin_unset(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		builtin_env(condition);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		builtin_cd(condition, node->argv);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		builtin_exit(condition, node);
	else
		ft_putstr_fd("error: builtin command not found\n", STDERR_FILENO);
}

static bool	convert_list_to_array(t_item *environ, char **ft_envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (environ)
	{
		temp = ft_strjoin(environ->key, "=");
		if (!temp)
			return (false);
		ft_envp[i] = ft_strjoin(temp, environ->value);
		if (!ft_envp[i])
			return (free_argv(ft_envp), false);
		free(temp);
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

static void	path_check(t_condition *condition, t_node *node, char *path)
{
	int	exit_status;

	exit_status = -1;
	if (!path)
		exit_status = not_found_error(node->argv[0]);
	else if (!ft_strncmp(path, ".", 2))
		exit_status = filename_required_error(node->argv[0]);
	else if (access(path, F_OK) != 0)
		exit_status = no_file_error(node->argv[0]);
	else if (!is_executable(path))
		exit_status = EXIT_NOT_EXECUTABLE;
	else if (path[0] == '\0')
		exit_status = EXIT_SUCCESS;
	if (exit_status != -1)
	{
		free(path);
		free_node(node);
		free_argv(condition->envp);
		exit(exit_status);
	}
}

int	execute(t_condition *condition, t_node *node)
{
	char	*path;

	if (!interpret_redirect(condition, node))
		free_exit(NULL, node, NULL, EXIT_FAILURE);
	if (node->argv[0] == NULL)
	{
		close_child_process_fd(node);
		free_exit(NULL, node, NULL, EXIT_SUCCESS);
	}
	set_redirect_fd(node);
	close_child_process_fd(node);
	make_envp(condition);
	if (is_builtin(node->argv[0]))
	{
		execute_builtin(condition, node);
		free_exit(condition, node, NULL, EXIT_SUCCESS);
	}
	path = get_path(condition, node->argv[0]);
	path_check(condition, node, path);
	execve(path, node->argv, condition->envp);
	put_execve_error(path);
	free_exit(condition, node, path, EXIT_NOT_EXECUTABLE);
	exit(EXIT_FAILURE);
}
