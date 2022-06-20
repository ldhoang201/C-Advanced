#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <D:\Codingz\C-advance\week3+\lib\jrb.h>
#include <D:\Codingz\C-advance\week3+\lib\fields.h>
#include <D:\Codingz\C-advance\week3+\lib\jrb.c>
#include <D:\Codingz\C-advance\week3+\lib\fields.c>
#include <D:\Codingz\C-advance\week3+\lib\jval.h>
#include <D:\Codingz\C-advance\week3+\lib\jval.c>
JRB modift_pbook(JRB tree,char * key,char *val)
{
    if(jrb_find_str(tree,key) != NULL && jrb_find_str(tree,val) != NULL)
    {
        jrb_delete_node(tree);
        (void)jrb_insert_str(tree,key,new_jval_s(val));
    }
    else (void)jrb_insert_str(tree,key,new_jval_s(val));
}
void add_phonebook(JRB pbook,char * key,char * val)
{
    jrb_insert_str(pbook,key,new_jval_s(val));
}
void delete_pbook(JRB pbook,char * key)
{
    jrb_delete_node(jrb_find_str(pbook,key));
}
int main()
{
    JRB pbook;
    JRB bn,temp;
    pbook = make_jrb();
    IS is;
    char *findname;
    char newname[20],newphone[20];
    is = new_inputstruct("pb.txt");
    while (get_line(is) >= 0)
    {
        char * name = strdup(is->text1);
        name[strlen(name)-1] = '\0';
        get_line(is);
        char * phone = strdup(is->text1);
        add_phonebook(pbook,name,phone);
    }
    delete_pbook(pbook,"Linh");
    //pbook=modift_pbook(pbook,newname,newphone);
    jrb_traverse(bn,pbook)
    {
        printf("%s%s",bn->key.s,bn->val.s);
    }
    printf("\n");
    return 0;
}