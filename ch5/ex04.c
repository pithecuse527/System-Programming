#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[256];
    if((fp = fopen(argv[1], "w+")) == NULL)
    {
        fprintf(stderr, "error - fopen()");
        exit(1);
    }
    fputs("Input String >> ", stdout);
    fgets(buf, sizeof(buf)-1, stdin);
    fputs(buf, fp);
    rewind(fp);
    fgets(buf, sizeof(buf)-1, fp);
    puts(buf);
    fclose(fp);
    exit(0);
}
