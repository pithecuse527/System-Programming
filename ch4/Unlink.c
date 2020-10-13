#include "apue.h"
#include <fcntl.h>

int main()
{
    if(open("Untitled", O_RDWR) < 0) err_sys("open error");
    if(unlink("Untitled") < 0) err_sys("unlink error");
    printf("file unlinked!\n");
    sleep(5);
    printf("done\n");
    exit(0);
}