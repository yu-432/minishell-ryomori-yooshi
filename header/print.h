/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:41 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/15 12:00:27 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

void	put_error(char *str);
void	put_syntax_error(char *str);
void	put_tokenizer_error(char *str);
void	put_unexpected_token_error(char *token);
void	put_unclosed_quote_error(char quote);
void	put_heredoc_warning(char *delimiter);
void	put_redirect_error(t_condition *condition, char *str);
void	export_error(t_condition *cond, char *str, char *perr);
void	put_export_error(t_condition *condition, char *argv);
int		not_found_error(char *str);
int		no_file_error(char *str);
void	put_execve_error(char *path);

#endif