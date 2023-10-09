#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    fork();
    fork();
    fork();
    printf("this is PID: %d \n", getpid());

       return 0;
}