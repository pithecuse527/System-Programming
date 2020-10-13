#include "apue.h"
#include <fcntl.h>

int main()
{
    int fd = open("foo", O_RDWR);
    ftruncate(fd, 3);
    exit(0);
}