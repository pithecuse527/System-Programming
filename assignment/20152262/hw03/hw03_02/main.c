#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = {"USER=HONGGEUN", NULL};

int main(int argc, char *argv[])
{
    pid_t pid;
    switch(atoi(argv[1]))
    {
        case 1:
            if((pid = fork()) < 0)
            {
                fprintf(stderr, "fork error\n");
                exit(-1);
            }
            else if(pid == 0)
            {
                if (execlp("./show_env", "show_env", (char*)0) < 0)
                {
                    fprintf(stderr, "execlp error\n");
                    exit(-1);
                }
            }
            else
            {
                if(waitpid(pid, NULL, 0) < 0)
                {
                    fprintf(stderr, "waitpid error\n");
                    exit(-1);
                }
                fprintf(stdout, "Print USER of env_var Complete!!\n");
            }
            break;
        case 2:
            if((pid = fork()) < 0)
            {
                fprintf(stderr, "fork error\n");
                exit(-1);
            }
            else if(pid == 0)
            {
                if (execle("./show_env", "show_env", (char*)0, env_init) < 0)
                {
                    fprintf(stderr, "execle error\n");
                    exit(-1);
                }
            }
            else
            {
                if(waitpid(pid, NULL, 0) < 0)
                {
                    fprintf(stderr, "waitpid error\n");
                    exit(-1);
                }
                fprintf(stdout, "Print USER of env_var Complete!!\n");
            }
            break;
        case 3:
            if((pid = fork()) < 0)
            {
                fprintf(stderr, "fork error\n");
                exit(-1);
            }
            else if(pid == 0)
            {   
                char *arguments[] = {"show_env", 0};
                if (execvp("./show_env", arguments) < 0)
                {
                    fprintf(stderr, "execlp error\n");
                    exit(-1);
                }
            }
            else
            {
                if(waitpid(pid, NULL, 0) < 0)
                {
                    fprintf(stderr, "waitpid error\n");
                    exit(-1);
                }
                fprintf(stdout, "Print USER of env_var Complete!!\n");
            }
            break;
        case 4:
            if((pid = fork()) < 0)
            {
                fprintf(stderr, "fork error\n");
                exit(-1);
            }
            else if(pid == 0)
            {   
                char *arguments[] = {"show_env", 0};
                if (execve("./show_env", arguments, env_init) < 0)
                {
                    fprintf(stderr, "execve error\n");
                    exit(-1);
                }
            }
            else
            {
                if(waitpid(pid, NULL, 0) < 0)
                {
                    fprintf(stderr, "waitpid error\n");
                    exit(-1);
                }
                fprintf(stdout, "Print USER of env_var Complete!!\n");
            }
            break;
    }
}