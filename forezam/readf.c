#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct readf
{
    char name[30];
    int num;
} profile;
int main()
{
    FILE *ptr;
    profile pro[20];
    int count = 0;
    ptr = fopen("name.txt","r");
    while(!feof(ptr))
    {
        fscanf(ptr,"%s",pro[count].name);
        fscanf(ptr,"%d",&pro[count].num);
        count++;
    }
    for(int i = 0;i < count;i ++)
    {
        printf("%s %d",pro[i].name,pro[i].num);
       if(i < count - 1)
       printf("\n");
    }
    fclose(ptr);
    return 0;
}