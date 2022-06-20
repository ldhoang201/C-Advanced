#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
int compare_str(void * key1, void* key2) {
    return strcmp((char*)key1, (char*)key2);
}
typedef struct {
    void * key;
    void * value;
} Entry;
typedef struct {
    Entry * entries;
    int total;
    int size;
}Symtab;
Symtab createPhoneSymtab()
{
    Symtab * temp;
    temp=malloc(sizeof(Symtab)*INITIAL_SIZE);
    temp->entries=malloc(sizeof(Entry)*INITIAL_SIZE);
    temp->size=0;
    temp->total=INITIAL_SIZE;
    return *temp;
}
void addSymtab(void * key,void * value,Symtab * pb)
{
    int id=pb->size;
    memcpy(pb->entries[id].key,key,sizeof(char*));
    memcpy(pb->entries[id].key,value,sizeof(char*));
    pb->size++;
}
Entry * getSymValue(void * name,Symtab sym)
{
    for(int i = 0;i < sym.size;i ++)
    {
        if(compare_str(sym.entries[i].key,name)==0)
        return &sym.entries[i];
    }
}
void Traveller(Symtab pb)
{
    for(int j = 0;j < pb.size;j ++)
    {
        printf("%s",(char*)pb.entries[j].key);
        printf("%s\n",(char*)pb.entries[j].value);
    }
}
int main()
{
    Symtab sym;
    sym=createPhoneSymtab();
    Entry *e;
    char *s;
    addSymtab("Linh","12A1",&sym);
    addSymtab("Trang","12A2",&sym);
    addSymtab("Yen","12A5",&sym);
    printf("%s",(char*)sym.entries[1].key);
    e=getSymValue("Trang",sym);
    if(e != NULL)
    printf("The Number of Trang is:%s\n",e->value);
    return 0;
}