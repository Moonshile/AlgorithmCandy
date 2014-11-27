#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_HASH_VALUE (0)
typedef const char* HashType;

//*************************************** hash **************************************************
typedef struct __hash_table__ {
    HashType* table;
    int capacity;
} HashTable;
HashTable* newHashTable(int capacity);
int hashStr(const char* key, int capacity);
int hashInt(int key, int capacity);
int findInHashTable(HashTable* table, HashType v, int (*hash)(HashType, int), int (*cmp)(const void*, const void*));
void insertIntoHashTable(HashTable* table, HashType v, int (*hash)(HashType, int), int (*cmp)(const void*, const void*));
void freeHashTable(HashTable* table);

//*************************************** hash **************************************************

HashTable* newHashTable(int capacity) {
    HashTable* t = (HashTable*)malloc(sizeof(HashTable));
    int i;
    t->table = (HashType*)malloc(sizeof(HashType)*capacity);
    for(i = 0; i < capacity; i++) {
        t->table[i] = EMPTY_HASH_VALUE;
    }
    t->capacity = capacity;
    return t;
}

int hashStr(const char* key, int capacity) {
    unsigned int v = 0;
    while(*key != 0) {
        v = (v << 5) + *key++;
    }
    return v%capacity;
}

int hashInt(int key, int capacity) {
    return key%capacity;
}

int findInHashTable(HashTable* table, HashType v, int (*hash)(HashType, int), int (*cmp)(const void*, const void*)) {
    int p = hash(v, table->capacity), collision = 0;
    while(table->table[p] != EMPTY_HASH_VALUE && cmp(table->table + p, &v) != 0) {
        // (x+1)^2 = x^2 + 2(x+1) - 1
        p += ((++collision)<<1) - 1;
        if(p >= table->capacity) {
            p -= table->capacity;
        }
    }
    return p;
}

void insertIntoHashTable(HashTable* table, HashType v, int (*hash)(HashType, int), int (*cmp)(const void*, const void*)) {
    table->table[findInHashTable(table, v, hash, cmp)] = v;
}

void freeHashTable(HashTable* table) {
    free(table->table);
    free(table);
}

//*************************************** test **************************************************

int compare(const void* x, const void* y) {
    return strcmp(*((HashType*)x), *((HashType*)y));
}

int main() {
    int capacity = 11, i;
    HashTable* t = newHashTable(capacity);
    insertIntoHashTable(t, "aesfaga", &hashStr, &compare);
    insertIntoHashTable(t, "sgs", &hashStr, &compare);
    insertIntoHashTable(t, "rhse", &hashStr, &compare);
    insertIntoHashTable(t, "aeserhfaga", &hashStr, &compare);
    insertIntoHashTable(t, "sjtshesrhserheshesh", &hashStr, &compare);
    for(i = 0; i < capacity; i++) {
        if(t->table[i]) {
            printf("%s\n", t->table[i]);
        }
    }
    freeHashTable(t);
    return 0;
}


