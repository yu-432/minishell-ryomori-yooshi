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



int	main()
{
	char	*command[][3] = {{"ls", NULL}, {"grep", ".c", NULL}, {"wc", "-l", NULL}};

	int	num_com = 3;
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

			execvp(command[i][0], command[i]);
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
	return(0);
	
}








// int main()
// {
// 	pid_t	pid_1;
// 	pid_t	pid_2;
// 	int		fds[2];

// 	if(pipe(fds) < 0)
// 		exit (1);
// 	pid_1 = fork();
// 	if (pid_1 == -1)
// 		exit(1);
// 	if (pid_1 == 0)
// 	{
// 		if (close(fds[0]) == -1)
// 			exit(1);
// 		if(fds[1] != STDOUT_FILENO)
// 		{
// 			if(dup2(fds[1], STDOUT_FILENO) == -1)
// 				exit(1);
// 			if(close(fds[1]) == -1)
// 				exit(1);
// 		}

// 		//ここにnode_leftのポインタを処理に渡す。返り値はnode_leftの処理の結果
// 		execlp("ls", "ls", (char *) NULL);
// 	}

// 	pid_2 = fork();
// 	if (pid_2 < 0)
// 		exit(1);
// 	if (pid_2 == 0)
// 	{
// 		if (close(fds[1]) == -1)
// 			exit(1);
// 		if (fds[0] != STDIN_FILENO)
// 		{
// 			if (dup2(fds[0], STDIN_FILENO) == -1)
// 				exit(0);
// 			if (close(fds[0]) == -1)
// 				exit(1);
// 		}
		
// 		//ここにnode_rigntのポインタを処理に渡す。返り値はnode_rigntの処理の結果
// 		execlp("wc", "wc", "-l", (char *) NULL);
// 	}

// 	if (close(fds[0]) == -1)
// 		exit(0);
// 	if (close(fds[1]) == -1)
// 		exit(0);
// 	waitpid(pid_1, NULL, 0);
// 	waitpid(pid_2, NULL, 0);
// 	return (0);
	
	
// }


// int main ()
// {
//     pid_1_t   pid_11;
//     pid_1_t   pid_12;
//     int fds[2];
    

//     pipe(fds); 
//     pid_11 = fork();
//     if (pid_11 == 0)
//     {
//         close(fds[0]);
//         // printf("fds[0]%d,fds[1]%d\n", fds[0], fds[1]);
	
//         dup2(fds[1], STDOUT_FILENO);
//         close(fds[1]);
//         		// example
// 		execlp("ls", "ls", (char *) NULL);
//     }
//     if(pid_11 < 0)
//     {
//         exit (1);
//     }

//     pid_12 = fork();//uwagakisareru;
//     if(pid_12 == 0)
//     {
//         if(close(fds[1]) == -1)
//             exit(1);
//         if (dup2(fds[0], STDIN_FILENO) == -1)
//                 exit(1);
//         if (close(fds[0]) == -1)
//             exit(1);
//             // example
//         execlp("wc", "wc", "-l", (char *) NULL);
//     }
//     if(pid_12 < 0)
//     {
//         exit (1);
//     }


//     close(fds[0]);
//     close(fds[1]);
//     waitpid_1(pid_11, NULL, 0);
//     waitpid_1(pid_12, NULL, 0);
//     return(0);

// }
