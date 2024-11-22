#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid<0){
        printf("Process failed");
        return 1;
    }else if(pid==0){
        printf("This is child process with PID: %d\n", getpid());
        printf("Child's parent PID is: %d\n", getppid());
    }else{
        printf("This is parent process with PID: %d\n", getpid());
        printf("Parent created a child process with PID: %d\n", pid);
    }
    return 0;
}