/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:39:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/24 17:16:04 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/print.h"

void	numeric_argument_error(char *argment)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argment, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(EXIT_NOT_NUM);
}

int	tma_error_check(t_condition *condition, char **args)
{
	if (args[2] != NULL)
	{
		put_error("exit: too many arguments");
		condition->exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

int	not_found_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (EXIT_NOT_FOUND);
}

int	no_file_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (EXIT_NOT_FOUND);
}

void	put_execve_error(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	perror(": ");
}
