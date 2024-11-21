/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:53:56 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/20 15:28:27 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FUNC_H
# define BUILTIN_FUNC_H

# include "execution.h"
# include "types.h"
# include "enums.h"
# include "print.h"
# include "init.h"
# include "../libft/libft.h"
# include <limits.h>
# include <sys/stat.h>

void	builtin_echo(char **argv);
void	builtin_env(t_condition *condition);
void	builtin_export(t_condition *condition, char **argv);
void	builtin_unset(t_condition *condition, char **argv);
void	builtin_pwd(void);
void	builtin_cd(t_condition *cond, char **args);
void	builtin_exit(t_condition *condition, t_node *node);

//cd_utils
int		update_cwd(t_condition *cond, char *newcwd);
char	*lst_getenv(t_item *item, char *key);
void	put_cd_error(t_condition *cond, char *str, char *perr);
int		move_path(int option);
int		update_old_pwd(t_condition *cond);
char	*get_item_value(t_item *item, char *key);
int		update_item_value(t_condition *cond, t_item *item, const char *cwd);
int		count_cd_arg(char **args);
//exit_utils
void	numeric_argument_error(char *argment);
int		tma_error_check(t_condition *condition, char **args);
char	*skip_space(char *str);
int		get_sign_skip0(char **str);
void	all_free(t_condition *condition, t_node *node);
//exit_utils2
long	over_256(long num);
long	negative_num(long num);
long	exit_status_num(long num);
bool	is_check_num(char *str);
//export_utils
void	has_not_argv(t_condition *condition);

#endif