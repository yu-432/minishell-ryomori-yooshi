/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/13 01:19:34 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "standard.h"
# include "token.h"

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

typedef struct s_token
{
	char			*token;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

#endif