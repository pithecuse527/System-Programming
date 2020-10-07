#include "../apue.h"
#include <fcntl.h>

main()
{
    int fd;
    fd = open("/etc/passwd", O_RDONLY);
    // fd = open("etc/passwd", O_RDWR)
    
    // fd = open("ap", O_RDWR | O_APPEND);
    // fd = open("ap", O_RDWR | O_CREAT | O_EXCEL, 0644);
    printf("%d\n", fd);
    fd = close(fd);
    printf("%d\n", fd);
}
