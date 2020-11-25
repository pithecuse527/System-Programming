#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    
    printf("USER=%s\n", getenv("USER"));
    exit(0);
}