/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 03:41:28 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/condition.h"
#include "../../header/execution.h"
#include "../../header/standard.h"
#include "../../libft/libft.h"
#include "../../header/builtin_func.h"
#include "../../header/print.h"

bool	is_spase(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*skip_space(char *str)
{
	while (is_spase(*str))
		str++;
	return (str);
}

int	get_sign_skip0(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '-' || **str == '+')
		str++;
	while (**str == '0')
		str++;
	return (sign);
}

static void	free_condition(t_condition *condition)
{
	t_item	*temp;

	while (condition->environ)
	{
		temp = condition->environ->next;
		free(condition->environ->key);
		free(condition->environ->value);
		free(condition->environ);
		condition->environ = temp;
	}
}

void	all_free(t_condition *condition, t_node *node)
{
	free_node(node);
	free_condition(condition);
}
