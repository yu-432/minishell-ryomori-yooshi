/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:58:05 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/23 14:10:36 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/main.h"

volatile sig_atomic_t	g_sig = 0;

char	*read_command_line(void)
{
	char	*line;

	line = readline(PROMPT);
	if (!line)
		return (NULL);
	if (*line != '\0')
		add_history(line);
	return (line);
}

void	init_condition(t_condition *condition)
{
	errno = 0;
	setup_parent_signal();
	if (g_sig)
	{
		condition->exit_status = g_sig + 128;
		g_sig = 0;
	}
}

void	shell_loop(t_condition *condition)
{
	char	*line;
	t_token	*tokenized;

	while (true)
	{
		init_condition(condition);
		line = read_command_line();
		if (!line)
			line = ft_strdup("exit");
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		tokenized = lexer(condition, line);
		free(line);
		run_command(condition, tokenized);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_condition	condition;

	if (argc != 1)
		return (put_error("minishell: too many arguments"), 1);
	if (!init_shell(&condition, envp))
		return (put_error(strerror(errno)), 1);
	shell_loop(&condition);
	rl_clear_history();
	(void)argv;
	exit(condition.exit_status);
}
