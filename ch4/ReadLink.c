#include <unistd.h>
#include <stdio.h>

int main()
{
    char read_str[200];
    int read = readlink("Unlink2.c", read_str, 200);
    printf("%d\n", read);
    printf("%s\n", read_str);
    
}