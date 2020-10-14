#include "../apue.h"

int main()
{
    char name[L_tmpnam], line[MAXLINE];
    
    FILE *fp;
    
    printf("%s\n", tmpnam(NULL));
    
    tmpnam(name);
    printf("%s\n", name);
    
    if ((fp = tmpfile()) == NULL) err_sys("tmpfile error");
    fputs("one line of output\n", fp);
    rewind(fp);
    sleep(20);
    if (fgets(line, sizeof(line), fp) == NULL) err_sys("fgets error");
    fputs(line, stdout);
    sleep(20);
    
    exit(0);
}
