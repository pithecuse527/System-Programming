#include "../apue.h"

int main()
{
    pid_t pid;
    
    if ((pid = fork()) < 0) err_sys("fork error");
    else if (pid == 0)
    {
        if ((pid = fork()) < 0) err_sys("fork error");
        else if (pid > 0) exit(0);  // this will make the second child a orphanage
        
        // the following codes are for second child (parent == first child)
        // init process will be a parent for second child
        sleep(2);   // wait for the first child's exit
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }
    
    if (waitpid(pid, NULL, 0) != pid) err_sys("waitpid error");     // wait for the first child
    printf("The parent, first child pid = %ld\n", (long)pid);
    exit(0);
}