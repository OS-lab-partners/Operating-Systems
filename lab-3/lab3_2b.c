#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int arg, char *argv[], char *env[])
{
    int x = 1;
    if (fork() == 0)
        printf("printf1: x = %d\n", ++x);
    printf("printf2: x = %d\n", --x);
    return 0;
}

    //Printf2: x = 0 x decremented to zero and printed in both parent and child process
    //Printf1: x = 2 child process incremented to 2 w/ both sharing this value
    //Printf2: x = 1 after incrementing the child process x is decremented to 1 and print in both parent and child process