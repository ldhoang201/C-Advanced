#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
typedef struct {
    char name[80];
    long number;
} PhoneEntry;
typedef struct {
    PhoneEntry * entries;
    int total;
    int size;
} PhoneBook;
PhoneBook createPhoneBook()
{
    PhoneBook * temp;
    temp=malloc(sizeof(PhoneBook)*INITIAL_SIZE);
    temp->entries=malloc(sizeof(PhoneEntry)*INITIAL_SIZE);
    temp->size=0;
    temp->total=INITIAL_SIZE;
    return *temp;
}
void addPhoneBook(char * name,long number,PhoneBook * pb)
{
    int id=pb->size;
    pb->entries[id].number=number;
    strcpy(pb->entries[id].name,name);
    pb->size++;
}
PhoneEntry * getPhoneNumber(char * name,PhoneBook book)
{
    for(int i = 0;i < book.size;i ++)
    {
        if(strcmp(book.entries[i].name,name) == 0)
        return &book.entries[i];
    }
}
void Traveller(PhoneBook pb)
{
    for(int j = 0;j < pb.size;j ++)
    {
        printf("%-20s",pb.entries[j].name);
        printf("%10d\n",pb.entries[j].number);
    }
}
int main()
{
    PhoneBook book;
    book=createPhoneBook();
    PhoneEntry *e;
    addPhoneBook("Linh",12342,&book);
    addPhoneBook("Trang",12789,&book);
    addPhoneBook("Yen",12891,&book);
    e=getPhoneNumber("Trang",book);
    if(e != NULL)
    printf("The Number of Trang is:%d\n",e->number);
    printf("%-20s","Ten");
    printf("%9s","SDT\n");
    Traveller(book);
    return 0;
}