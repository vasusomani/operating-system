#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        printf("I am the child, my process ID is %d\n", getpid());
        printf("My parent's process ID is %d\n", getppid());
        sleep(6);
        printf("\nI am the child, my process ID is %d\n", getpid());
        printf("My parent's process ID is %d\n", getppid());
    }
    else
    {
        sleep(3);
        printf("I am the parent, my process ID is %d\n", getpid());
        printf("The parent's parent, process ID is %d\n", getppid());
        printf("Parent terminates\n");
        exit(0);
    }
}