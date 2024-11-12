/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:54:19 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONDITION_H
# define CONDITION_H

#define PROMPT "minishell$ "

typedef struct s_item
{
	char *key;
	char *value;
	struct s_item	*next;
}	t_item;

typedef struct s_condition
{
	t_item	*environ;
	char **envp;
	int		exit_status;
}	t_condition;

#endif