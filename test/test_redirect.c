#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
extern char **environ;

int main()
{
	// char *str1[3] = {"ls", "-l", NULL};
	// char *str2[3] = {"grep", ".c", NULL};

	int pipefd[2];
	pid_t	pid1, pid2;

	pipe(pipefd);

	if((pid1 = fork()) == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		execlp("ls", "ls", "-l", NULL);
		perror("exec");
		exit(1);
	}

	if ((pid2 = fork()) == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);

		int fd = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd < 0)
		{
			perror("open");
			exit(1);
		}

		dup2(fd, STDOUT_FILENO);
		close(fd);

		execlp("grep", "grep", ".c", NULL);
		perror("exec");
		exit(1);

		close(pipefd[0]);
		close(pipefd[1]);

		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);



		
	}
	

}