/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:35 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 17:52:19 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtin_func.h"

int	builtin_pwd(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
	{
		ft_putstr_fd("minishell:", STDERR_FILENO);
		perror("getcwd:");
		return (1);
	}
	else
	{
		write(STDOUT_FILENO, pwd_path, ft_strlen(pwd_path));
		write(STDOUT_FILENO, "\n", 1);
		free(pwd_path);
		return (0);
	}
}
