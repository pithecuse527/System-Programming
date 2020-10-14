#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    
    if((fp = fopen("test.txt", "r")) != NULL)
    {
        printf("Success!\n");
        printf("Opening \"test.txt\" in \"r\" mode!\n");
    }
    else
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    fclose(fp);
    exit(0);
}
