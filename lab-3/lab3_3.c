/**
 * @file lab3_3.c
 * @brief demonstrates fork() to create child process, displaying process IDs before and after sleep
 * @date 2023-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    // creates int to store process ID
    int pid;

    // creates two identical processes running simultaneously
    pid = fork();

    // checks if fork failed
    if (pid == -1)
    {
        perror("ERROR – fork \n");
        exit(0);
    }

    // if pid is zero, means the code is running in the child process
    else if (pid == 0)
    {
        printf("Child process with pid = %d, and Parent pid = %d\n",
        getpid(), getppid());
        sleep(5);
        printf("After sleeping. Child process with pid = %d, and Parent pid = %d\n", getpid(), getppid());
        exit(0);
    }

    // if pid is greater than zero, means the code is running in the parent process
    else {
        printf("Parent process with pid = %d, and Parent pid = %d\n",
        getpid(), getppid());
        printf("Parent exiting now\n");
        exit(0);
    }
    return 0;
}