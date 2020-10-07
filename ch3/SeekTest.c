#include "apue.h"
#include <unistd.h>
#include <fcntl.h>

main()
{
    off_t curpos;
    int fd;
    fd = open("MyCompile.sh", O_RDONLY);
    curpos = lseek(fd, 0, SEEK_CUR);
    
    int size = lseek(fd, 0, SEEK_END);      // the size of file
    printf("%d\n", size);
    
}
