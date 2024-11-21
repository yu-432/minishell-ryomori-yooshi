/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:24 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/21 12:03:19 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtin_func.h"

long	ft_atoll(const char *str)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return ((long)num * sign);
}

int	long_check_return(const char *argment, int sign)
{
	const char	*long_max_str;
	const char	*long_min_str;

	long_max_str = "9223372036854775807";
	long_min_str = "9223372036854775808";
	if (sign == 1)
	{
		if (ft_strncmp(argment, long_max_str, 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(argment, long_min_str, 19) > 0)
			return (1);
	}
	return (0);
}

int	long_over_check(char *argment)
{
	int			i;
	int			sign;

	sign = 1;
	i = 0;
	sign = get_sign_skip0(&argment);
	i = ft_strlen(argment);
	if (i > 19)
		return (1);
	if (i < 19)
		return (0);
	return (long_check_return(argment, sign));
}

int	exit_with_argment(t_condition *condition, t_node *node, char *argment, \
						char **args)
{
	long	num;
	int		judge;
	long	result;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (tma_error_check(condition, args))
		return (1);
	judge = long_over_check(argment);
	if (judge == 1)
	{
		numeric_argument_error(argment);//この関数内でputstr exitしているため、このエラーに引っかかる場合２回出力される
		return (1);
	}
	num = ft_atoll(argment);
	result = exit_status_num(num);
	exit(result);
	all_free(condition, node);
	return (0);
}

int	builtin_exit(t_condition *condition, t_node *node)
{
	char	*argment;

	if (node->argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		all_free(condition, node);
		exit(condition->exit_status);
	}
	argment = (skip_space(node->argv[1]));
	if (!is_check_num(argment))
	{
		numeric_argument_error(argment);
		return (1);
	}
	return (exit_with_argment(condition, node, argment, node->argv));
}
