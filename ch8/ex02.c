#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;

int main()
{
    int var;
    pid_t pid;
    
    var = 88;
    printf("before vfork\n");
    if((pid=vfork()) < 0) {
        printf("vfork error");
        return -1;
    } else if (pid == 0) {
        glob++;
        var++;
        exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n",getpid(),glob,var);
    exit(0);
}