#include "apue.h"

int main(void)
{
    struct stat buf;
    stat("foo", &buf);
    printf("Before link count = %d\n", (int)buf.st_nlink);
    link("foo", "foo.ln");
    stat("foo", &buf);
    printf("After link count = %d\n", (int)buf.st_nlink);
    return 0;
}