/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:56:50 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/14 21:15:42 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"
#include "../../header/standard.h"
#include "../../header/condition.h"
#include "../../header/token.h"
#include "../../libft/libft.h"
#include "../../header/lexer.h"

static int	count_pipe(t_node *node)
{
	int	count;

	count = 0;
	while (node)
	{
		if (get_token_kind(node->argv[0]) == TOKEN_PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

static bool	init_exec_info(t_exec_info *info, t_node *node)
{
	ft_memset(info, 0, sizeof(t_exec_info));
	info->keep_fd = -2;
	info->pipe_count = count_pipe(node);
	info->pid = ft_calloc(info->pipe_count + 1, sizeof(pid_t));
	if (!info->pid)
		return (false);
	return (true);
}

static bool process_heredoc(t_condition *condition, t_node *node)
{
	t_node	*current;

	current = node;
	while (current)
	{
		if (current->kind == NODE_CMD)
		{
			if (!exec_heredoc(condition, current))
				return (false);
		}
		current = current->next;
	}
	return (true);
}

static bool	exec_command(t_condition *condition, t_node *node)
{
	t_node		*current;
	t_exec_info	info;

	condition->exit_status = 0;
	if (!process_heredoc(condition, node))
		return (false);
	if (node->next == NULL && node->argv[0] != NULL)
		return (execute_single_command(condition, node), true);
	current = node;
	if (!init_exec_info(&info, node))
		return (false);
	while (current->next)
	{
		if (current->kind == NODE_CMD)
		{
			if (!execute_pipeline_cmd(condition, current, &info))
				return (false);
		}
		current = current->next;
	}
	return (execute_last_pipeline_cmd(condition, current, &info));
}

void	run_command(t_condition *condition, t_token *token_list)
{
	t_node	*node;

	if (!token_list)
		return ;
	node = make_node(condition, token_list);
	free_tokens(token_list);
	if (node == NULL)
		return ;
	exec_command(condition, node);
	free_node(node);
	(void)condition;
	return ;
}
