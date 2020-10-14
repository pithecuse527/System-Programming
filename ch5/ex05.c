#include <stdio.h>
#include <stdlib.h>

struct student{
    int sno;
    char name[10];
    int point;
};

int main()
{
    struct student s1, s2;
    FILE *fp;
    
    fputs("input sno >> ", stdout);
    scanf("%d", &s1.sno);
    fputs("input name >> ", stdout);
    scanf("%s", &s1.name);
    fputs("input pint >> ", stdout);
    scanf("%d", &s1.point);
    
    if((fp = fopen("student.dat", "w")) == NULL)
    {
        fprintf(stderr, "error - fopen()\n");
        exit(1);
    }
    if(fwrite(&s1, sizeof(struct student), 1, fp) != 1)
    {
        fprintf(stderr, "error - fwrite()\n");
        exit(1);
    }
    fclose(fp);
    
    if((fp = fopen("student.dat", "r")) == NULL)
    {
        fprintf(stderr, "error - fopen()\n");
        exit(1);
    }
    if(fread(&s2, sizeof(struct student), 1, fp) != 1)
    {
        fprintf(stderr, "error - fwrite()\n");
        exit(1);
    }
    fclose(fp);
    
    printf("no : %d\nname : %s\npoint : %d\n", s2.sno, s2.name, s2.point);
    exit(0);
    
}