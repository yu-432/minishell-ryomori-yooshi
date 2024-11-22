/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:25:56 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/22 19:33:56 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "enums.h"
# include <sys/types.h>

typedef struct s_item	t_item;

typedef struct s_condition
{
	t_item	*environ;
	char	**envp;
	int		exit_status;
}	t_condition;

typedef struct s_node
{
	t_node_kind		kind;
	char			**argv;
	int				fd_in;
	int				fd_out;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_token
{
	char			*token;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef struct s_expand
{
	char *new;
	int index;
	char quote;
}	t_expand;

typedef struct s_item
{
	char			*key;
	char			*value;
	struct s_item	*next;
}	t_item;

typedef struct s_exec_info
{
	pid_t	*pid;
	int		keep_fd;
	int		pipe_count;
	int		executed_count;
}	t_exec_info;

typedef struct s_lexer
{
	char	*env_key;
	char	quote;
}	t_lexer;

#endif