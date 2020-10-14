#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

int main()
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;
    
    char *nm = "test.txt";
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);
    
    printf("%s\n", nm);
    nm = tmpnam(NULL);
    printf("%s\n", nm);
    
    if((fp = tmpfile()) == NULL)
    {
        fprintf(stderr, "error - tmpfile()\n");
        exit(1);
    }
    fputs("one line of output\n", fp);
    rewind(fp);
    
    if(fgets(line, sizeof(line), fp) == NULL)
    {
        fprintf(stderr, "error - fgets()\n");
        exit(1);
    }
    fputs(line, stdout);
    exit(0);
}