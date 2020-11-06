#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int i=0;
    int retval;
    retval = system("ls -al");
    printf("exit status %d\n", retval);
    return 0;
}