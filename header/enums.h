/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:28:51 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/23 14:09:11 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# define INVALID_FD -2
# define INPUT_EOF 1
# define EXIT_NUMERIC 2
# define EXIT_SYNTAX 2
# define EXIT_NOT_EXECUTABLE 126
# define EXIT_NOT_FOUND 127
# define EXIT_SIGINT 130
# define SHLVL_MAX 999

typedef enum e_move_position
{
	MOVE_TO_HOME,
}	t_move_position;

typedef enum e_std_fd
{
	IN,
	OUT,
	ERR
}	t_std_fd;

typedef enum e_node_kind
{
	NODE_CMD,
	NODE_PIPE
}	t_node_kind;

typedef enum e_token_kind
{
	TOKEN_UNKNOWN,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_EOF,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
}	t_token_kind;

#endif