
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main ()
{
    pid_t   pid1;
    pid_t   pid2;
    int fds[2];
    

    pipe(fds); 
    pid1 = fork();
    if (pid1 == 0)
    {
        close(fds[0]);
        // printf("fds[0]%d,fds[1]%d\n", fds[0], fds[1]);
	
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
        		// example
		execlp("ls", "ls", (char *) NULL);
    }
    if(pid1 < 0)
    {
        exit (1);
    }

    pid2 = fork();//uwagakisareru;
    if(pid2 == 0)
    {
        if(close(fds[1]) == -1)
            exit(1);
        if (dup2(fds[0], STDIN_FILENO) == -1)
                exit(1);
        if (close(fds[0]) == -1)
            exit(1);
            // example
        execlp("wc", "wc", "-l", (char *) NULL);
    }
    if(pid2 < 0)
    {
        exit (1);
    }


    close(fds[0]);
    close(fds[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return(0);

}
