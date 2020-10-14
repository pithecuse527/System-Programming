#include "../apue.h"
#define NAMESIZE 100

typedef struct item {
    short count;
    long total;
    char name[NAMESIZE];
} item;

int main()
{
    FILE *fp = fopen("TEST.txt", "r+");
    item a;
    float data[10];
    if(fwrite(&data, sizeof(float), 4, fp) != 4) err_sys("fwrite error");
    
    //if(fwrite(&a, sizeof(a), 1, fp) != 1) err_sys("fwrite error");
    exit(0);
}