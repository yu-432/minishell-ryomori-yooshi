/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:57:51 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/23 14:09:22 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/print.h"

void	put_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	put_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", \
					STDERR_FILENO);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	put_cd_error(t_condition *cond, char *str, char *perr)
{
	cond->exit_status = EXIT_FAILURE;
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (perr)
		perror(NULL);
	else
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	put_export_error(t_condition *condition, char *argv)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	condition->exit_status = EXIT_FAILURE;
}

void	export_error(t_condition *cond, char *str, char *perr)
{
	cond->exit_status = EXIT_FAILURE;
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (perr)
		perror(NULL);
	else
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}
