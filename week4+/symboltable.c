#include "symboltable.h"
SymbolTable* createSymbolTable(Entry* (*makeNode)(void*, void*), int(*compare)(const void*, const void*))
{
    SymbolTable* temp;
    temp = malloc(sizeof(SymbolTable));
    temp -> entries = malloc(INITIAL_SIZE * sizeof(Entry));
    temp -> makeNode = makeNode;
    temp -> compare = compare;
    temp -> total = 0;
    temp -> size = INITIAL_SIZE;
    return temp;
}

void addEntry(void* key, void* value, SymbolTable* book)
{
    int id = book -> total;
    book -> entries[id] = *(book -> makeNode(key, value));
    book -> total ++;
}

Entry* getEntry(void* key, SymbolTable* book)
{
    for (int i = 0; i < book -> total; i++)
    {
        if (book -> compare(book -> entries[i].key, key) == 0)
            return &book -> entries[i];
    } 
    return NULL;
}
void dropSymbolTable(SymbolTable* tab)
{
    for (int i = 0; i < tab -> total; i++)
    {
        free(tab -> entries[i].key);
        free(tab -> entries[i].value);
    }
    free(tab -> entries);
    free(tab);
}