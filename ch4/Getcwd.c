#include "apue.h"

int main()
{
    char *ptr;
    int size;
    
    if (chdir("out") < 0) err_sys("chdir failed");
    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL) err_sys("getcwd failed");
    printf("cwd = %s\n", ptr);
    printf("size = %d\n", size);
    exit(0);
}