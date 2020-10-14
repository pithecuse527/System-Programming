#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char str[100];
    
    fp = fopen("test.txt", "w");
    fputs("Hello World!!\n", fp);
    fp  = freopen("test.txt", "r", fp);
    fgets(str, 99, fp);
    printf("%s", str);
    fclose(fp);
    
    exit(0);
}