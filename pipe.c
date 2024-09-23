
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main ()
{
    pid_t   pid;
    int fds[2];

    fds[0] = 100;
    fds[1] = 200;

    pipe(fds); 
    pid = fork();
    if (pid > 0)
    {
        int status;

        // printf("before wait\n");
        waitpid(pid, &status, 0);
        
        close(fds[0]);
        // printf("fds[0]%d,fds[1]%d\n", fds[0], fds[1]);
        

        printf("parent\n");
        exit(0);
    }
    if (pid == 0)
    {
        printf("I am good\n");
        close(fds[1]);
        // printf("fds[0]%d,fds[1]%d\n", fds[0], fds[1]);
        exit(0);
    }
    else
    {
        fprintf(stderr, "error\n");
        exit (1);
    }

}