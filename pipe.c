/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryomori <ryomori@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-24 03:43:12 by ryomori           #+#    #+#             */
/*   Updated: 2024-09-24 03:43:12 by ryomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	char	*path;
	char	*args[3];
	char	**envp;
} parse_element;



void	command_pipe(parse_element element[], int num_com)
{
	int	fds[2];
	int	keep_fd = 0;
	pid_t	pid;
	int	i = 0;


	while (i < num_com)
	{
		if (i < num_com - 1 && pipe(fds) == -1)
		{
			exit(1);
		}

		pid = fork();
		if (pid == -1)
		{
			exit(1);
		}

		if (pid == 0)
		{
			if (keep_fd != 0)
			{
				if (dup2(keep_fd, STDIN_FILENO) == -1)
				{
					exit(1);
				}
				close(keep_fd);
			}

			if (i < num_com - 1)
			{
				close(fds[0]);
				if (dup2(fds[1], STDOUT_FILENO) == -1)
				{
					exit(1);
				}
				close(fds[1]);
			}

			execve(element[i].path, element[i].args, element[i].envp);
			exit(0);
		}
		else if (pid > 0)
		{
			if (keep_fd != 0)
				close(keep_fd);
			
			if (i < num_com - 1)
			{
				close (fds[1]);
				keep_fd = fds[0];
			}
		}
		i++;
	}

	i = 0;
	while (i < num_com)
	{
		wait(NULL);
		i++;
	}
}

int main()
{
	parse_element element[] = {{"/bin/ls",{"/bin/ls, NULL"}, NULL}, {"/bin/grep", {"/bin/grep", ".c"}, NULL}, {"/usr/bin/wc", {"/usr/bin/wc", "-l"}, NULL}};

	int i = 3; //commandの数

	command_pipe(element, i);
	return (0);
}
