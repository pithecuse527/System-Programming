#include "apue.h"

int main(void)
{
    char path[256];
    
    getcwd(path, 255);
    printf("Before chdir() - %s\n", path);
    if(chdir("/tmp") < 0)
    {
        fprintf(stderr, "chdir error\n");
        exit(1);
    }
    getcwd(path, 255);
    printf("After chdir() - %s\n", path);
    return 0;
}
