#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"
// phonebook generic
Entry* makeNode(void* key, void* value)
{
    Entry* temp = malloc(sizeof(Entry));
    temp -> key = strdup((char*)key);
    temp -> value = strdup((char*)value);
    return temp;
}

int compare(const void* elementKey, const void* key)
{
    return strcmp((char*)elementKey, (char*)key);
}
int main()
{
    SymbolTable* book = createSymbolTable(makeNode, compare);
    
}