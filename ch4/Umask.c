#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void)
{
    umask(0);
    printf("%d\n", RWRWRW);
    if(creat("foo", RWRWRW) < 0)
        err_sys("creat error for foo");
        
    printf("%d\n", umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH));
    
    if(creat("bar", RWRWRW) < 0)
        err_sys("creat error for bar");
        
    exit(0);
}
