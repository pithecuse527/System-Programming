#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c, number = 0;
    char buf[100];
    FILE *fp;
    
    if((fp = fopen("test.txt", "r")) == NULL)
    {
        fprintf(stderr, "File open error\n");
        exit(1);
    }
    while((c = fgetc(fp)) != EOF)
    {
        if(c == '#') ungetc('@', fp);
        else ungetc(c, fp);
        fgets(buf, 99, fp);
        fputs(buf, stdout);
    }
    
    exit(0);
}