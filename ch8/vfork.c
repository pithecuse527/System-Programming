#include "../apue.h"

int globvar = 6;

int main()
{
    int var;
    pid_t pid;
    var = 88;
    
    printf("before vfork\n");
    if((pid=vfork()) < 0) {
        err_sys("vfork error");
    }
    else if (pid == 0)
    {
        globvar++;	// accessing parent's variables
        var++;
        exit(0);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
