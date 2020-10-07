#include "apue.h"

int main(void)
{
    if(mkdir("ex05_test", 0755) == -1)
    {
        fprintf(stderr, "error - mkdir(ex05_test)\n");
        exit(1);
    }
    
    if(mkdir("ex05_new", 0755) == -1)
    {
        fprintf(stderr, "error - mkdir(ex05_new)\n");
        exit(1);
    }
    
    if(rename("ex05_new", "ex05_old") == -1)
    {
        fprintf(stderr, "error - rename(ex05_new)\n");
        exit(1);
    }
    
    if(rmdir("ex05_test") == -1)
    {
        fprintf(stderr, "error - rmdir(ex05_test)\n");
        exit(1);
    }
    return 0;
}