#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void process()
{
    // Process Creation and Execution
    pid_t pid = fork();
    int child_pid;
    int parent_pid;

    if (pid < 0)
    {
        // Fork failed
        perror("Child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child Process
        child_pid = getpid();
        printf("Child process execution with pid: %d\n", child_pid);

        // Process Termination
        int kill_status = kill(child_pid, SIGKILL);
        if (kill_status != 0)
        {
            printf("Child process termination failed with status: %d\n", kill_status);
        }
    }
    else
    {
        // Parent Process
        parent_pid = getpid();
        printf("Parent process execution with pid: %d\n\n", parent_pid);
    }
    printf("Hello World, its a proof that the process is not terminated yet!!!\n");
    int curr_pid = getpid();
    printf("PID is: %d\n\n", curr_pid);
}

int main()
{
    process();
    return 0;
}
