#include <string.h>
#ifndef __SYMBOLTABLE_H__

typedef struct {
    void* key;
    void* value;
}Entry;

typedef struct {
    Entry* entries;
    int total, size;
    Entry* (*makeNode)(void*, void*);
    int (*compare)(const void*, const void*);
}SymbolTable;
Entry* makeNode(void* key, void* value);
int compare(const void* elementKey, const void* key);
void addEntry(void* key, void* value, SymbolTable* book);
Entry* getEntry(void* key, SymbolTable* book);
void dropSymbolTable(SymbolTable* tab);
SymbolTable* createSymbolTable(Entry* (*makeNode)(void*, void*), int(*compare)(const void*, const void*));
#define INCREMENTAL_SIZE 5
#define INITIAL_SIZE 100
#endif