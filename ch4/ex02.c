#include "apue.h"

int main(void)
{
    chown("bar", getuid(), getgid());
    return 0;
}
