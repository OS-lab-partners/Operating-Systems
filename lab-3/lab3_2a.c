#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
    fork();
    printf("hello\n");
    return 0;
}