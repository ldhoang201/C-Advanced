#include<stdlib.h>
#include<stdio.h>
#include "bt-5.0.1\inc\btree.h"
void add_pbook(BTA * tree,char * name,long number)
{
    binsky(tree,name,number);
}
void delete_pbook(BTA * tree,char * name,long number)
{
    int x;
    bfndky(tree,name,&x);
    if(x == number)
    bdelky(tree,name);
}
void modify_pbook(BTA * tree,char * name,long number)
{
    int y;
    char ch;
    char newname[30];
    long newnumber;
    bfndky(tree,name,&y);
    if(y == number)
    {
        delete_pbook(tree,name,number);
        printf("Ban muon nhap Ten moi hay SDT moi(T/S):");scanf("%c",&ch);
        if(ch == 'T')
        {
            printf("Nhap Ten moi:");gets(newname);
            add_pbook(tree,newname,number);
        }
        if(ch == 'S')
        {   
            printf("Nhap SDT moi:");scanf("%ld",&newnumber);
            add_pbook(tree,name,newnumber);
        }
    }
    else add_pbook(tree,name,number);
}
int main()
{
    BTA *a;
    btinit();
    a=btcrt("sxz",0,FALSE);
    add_pbook(a,"Hoang",1234);
    add_pbook(a,"Hai",8984);
    add_pbook(a,"Long",8523);
    delete_pbook(a,"Long",8523);
    btcls(a);
    return 0;
}