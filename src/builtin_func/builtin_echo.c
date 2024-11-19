/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:11 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 17:48:09 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtin_func.h"

bool	echo_n_option(char *argment)
{
	int	j;

	j = 2;
	if (argment && !ft_strncmp(argment, "-n", 2))
	{
		while (argment[j] == 'n')
			j++;
		if (argment[j] == '\0')
			return (true);
	}
	return (false);
}

void	builtin_echo(char **argv)
{
	int		i;
	bool	is_newline;

	i = 1;
	if (argv[1] == NULL)
		return (ft_putstr_fd("\n", STDOUT_FILENO));
	is_newline = true;
	if (echo_n_option(argv[1]))
	{
		is_newline = false;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (is_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
