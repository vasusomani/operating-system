#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    // Parent process
    if (pid > 0)
    {
        printf("\nParent Process is going to sleep\n");
        sleep(10);
        printf("Parent process is resumed\n");
    }
    // Child process
    else if (pid == 0)
    {
        printf("\nChild process executing\n");
        printf("Child Terminates\n");
        exit(0);
    }
    return 0;
}