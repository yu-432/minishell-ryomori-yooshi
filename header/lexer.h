/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:37 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/19 18:12:33 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "condition.h"
# include "enums.h"
# include "types.h"
# include "standard.h"
# include "token.h"
# include "print.h"
# include "lexer.h"
# include "../libft/libft.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

//lexer
t_token	*lexer(t_condition *condition, char *line);

//tokenizer
t_token	*tokenizer(char *line);
t_token	*new_token(char *token, t_token_kind kind);
t_token	*find_tail_token(t_token *token);
bool	is_space(char c);
bool	is_quote(char c);
bool	is_metacharacter(char c);
int		get_token_kind(char *token);
int		count_same_char(char *line, char c);
void	free_tokens(t_token *token);

//expand
bool	expand_token(t_condition *condition, t_token *tokenized);
bool	append_char(char **str, char c);

//expand_dollar
bool	expand_dollar(t_condition *condition, t_token *tokenized);
bool	handle_dollar(t_condition *condition, char *token, \
							char **new, int *i);
char	*find_env(t_condition *condition, char *env_key);
bool	ft_strjoin_free(char **s1, char *s2);

//expand_quote
bool	expand_quote(t_token *tokenized);

//find_syntax_error
bool	find_syntax_error(t_token *tokenized);

#endif