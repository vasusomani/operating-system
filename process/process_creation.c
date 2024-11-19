#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process 1
        printf("Child 1: Running 'ls' command.\n");
        execlp("ls", "ls", NULL); 
    }
    else if (pid > 0)
    {
        wait(NULL);
        pid = fork();

        if (pid == 0)
        {
            // Child process 2
            printf("Child 2: Running 'pwd' command.\n");
            execlp("pwd", "pwd", NULL); 
        }
        else if (pid > 0)
        {
            wait(NULL);
            printf("Parent process: All children completed.\n");
        }
        else
        {
            printf("Fork failed!\n");
        }
    }
    else
    {
        printf("Fork failed!\n");
    }

    return 0;
}
