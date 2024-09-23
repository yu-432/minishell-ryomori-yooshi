
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main ()
{
    pid_t   pid;

    pid = fork();

    if (pid > 0)
    {
        int status;

        printf("before wait\n");
        waitpid(pid, &status, 0);
        printf("parent\n");
        exit(0);
    }
    if (pid == 0)
    {
        printf("I am good\n");
        exit(0);
    }
    else
    {
        fprintf(stderr, "error\n");
        exit (1);
    }

}