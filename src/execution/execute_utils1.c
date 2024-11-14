/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:45 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 13:39:11 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/lexer.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/execution.h"
#include "../../header/builtin_func.h"

bool	is_builtin(char *cmd)
{
	if (!cmd || *cmd == '\0')
		return (false);
	if (ft_strncmp(cmd, "echo", 5) == 0 || \
		ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "pwd", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 6) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0 || \
		ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	is_kind_redirect(t_token_kind kind)
{
	if (kind == TOKEN_REDIRECT_IN || \
		kind == TOKEN_REDIRECT_OUT || \
		kind == TOKEN_REDIRECT_APPEND || \
		kind == TOKEN_REDIRECT_HEREDOC)
		return (true);
	return (false);
}

bool	is_executable(char *path)
{
	struct stat	st;

	if (stat(path, &st))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (false);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (true);
	return (false);
}

int	count_environ(t_item *environ)
{
	int	count;

	count = 0;
	while (environ)
	{
		count++;
		environ = environ->next;
	}
	return (count);
}
