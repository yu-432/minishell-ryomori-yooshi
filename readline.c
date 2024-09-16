#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



int main (void)
{
    char    *line;

    while(1)
    {
        line = readline("minishell$ ");
        if (line == NULL)
            break;
        printf("%s\n", line);
        if(*line != '\0')
        {
            add_history(line);
        }
        free(line);
    }
    return(0);
}


// line -> 0x0asdjbu -> "abc"