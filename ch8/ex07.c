#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0) {
        execle("echoall", "echoall", "myarg1", "myarg2", (char*)0, env_init);
    }
    waitpid(pid, NULL, 0);
    pid = fork();
    if(pid ==0) {
        execlp("./echoall", "echoall", "only 1 arg", (char*)0);
    }
    return 0;
}