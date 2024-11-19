/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:55:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 17:34:51 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtin_func.h"

char	*skip_space(char *str)
{
	while (is_space(*str))
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
