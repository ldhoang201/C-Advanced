#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define element pbook
#define MAX 50
typedef struct 
{
    char name[30];
    char phone[20];
}pbook;
int compare(const char *a,const char *b)
{
    return strcmp(((pbook*)a)->name,((pbook*)b)->name);
}
void qsort1(pbook *buf,size_t num,size_t size,int (*compare)(const char*,const char*));
int main()
{
    FILE *ptr=fopen("phonebook.txt","r");
    pbook str[MAX];
    int count=0;
    while (!feof(ptr))
    {
        fgets(str[count].name,30,ptr);
        fgets(str[count].phone,30,ptr);
        count++;
    }
    qsort1(str,count,sizeof(pbook),compare);
    for(int i=0;i<count;i++)
    {
        printf("%s",str[i].name);
        printf("%s",str[i].phone);
    }
    return 0;
}