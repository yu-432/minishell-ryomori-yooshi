/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:54:33 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/12 23:54:35 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

bool	init_shell(t_condition *condition, char **envp);
bool init_environ(t_condition *condition, char **envp);
bool add_env(t_condition *condition, char *env_str);
t_item *touch_t_item();
t_item *find_tail(t_item *head);
t_item *search_dup_item(t_condition *condition, char *key);
bool insert_env(t_condition *condition, char *key, char *value);

# endif