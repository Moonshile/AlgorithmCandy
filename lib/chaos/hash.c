#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (1)
#define FALSE (0)

typedef int KeyType;
typedef int ValueType;

//*************************************** hash **************************************************
typedef struct __hash_node__ {
    KeyType key;
    ValueType value;
    int empty;
} HashNode, *HashNodePtr;

typedef struct __hash_table__ {
    HashNodePtr table;
    int capacity;
    int (*hash)(KeyType, int);
    int (*cmp)(const void*, const void*);
} HashTable, *HashTablePtr;

HashTablePtr newHashTable(int capacity, 
    int (*hash)(KeyType, int), 
    int (*cmp)(const void*, const void*));
int hashStr(const char* key, int capacity);
int hashInt(int key, int capacity);
HashNodePtr findInHashTable(HashTablePtr t, KeyType key);
void putIntoHashTable(HashTablePtr t, KeyType key, ValueType v);
HashNodePtr getFromHashTable(HashTablePtr t, KeyType key);
void freeHashTable(HashTablePtr t);

//*************************************** hash **************************************************

HashTablePtr newHashTable(int capacity, 
    int (*hash)(KeyType, int), 
    int (*cmp)(const void*, const void*)) {
    HashTablePtr t = (HashTablePtr)malloc(sizeof(HashTable));
    int i;
    t->table = (HashNodePtr)malloc(sizeof(HashNode)*capacity);
    for(i = 0; i < capacity; i++) {
        t->table[i].empty = TRUE;
    }
    t->capacity = capacity;
    t->hash = hash;
    t->cmp = cmp;
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

HashNodePtr findInHashTable(HashTablePtr t, KeyType key) {
    int p = t->hash(key, t->capacity), collision = 0;
    while(!(t->table[p].empty) && t->cmp(&(t->table[p].key), &key) != 0) {
        // (x+1)^2 = x^2 + 2(x+1) - 1
        p += ((++collision)<<1) - 1;
        if(p >= t->capacity) {
            p -= t->capacity;
        }
    }
    return t->table + p;
}

void putIntoHashTable(HashTablePtr t, KeyType key, ValueType v) {
    HashNodePtr node = findInHashTable(t, key);
    node->key = key;
    node->value = v;
    node->empty = FALSE;
}

HashNodePtr getFromHashTable(HashTablePtr t, KeyType key) {
    HashNodePtr node = findInHashTable(t, key);
    if(node->empty) {
        return NULL;
    }
    return node;
}

void freeHashTable(HashTablePtr t) {
    free(t->table);
    free(t);
}

//*************************************** test **************************************************

int compare(const void* x, const void* y) {
    return *(KeyType*)x - *(KeyType*)y;
}

int main() {
    int capacity = 11, i;
    HashTablePtr t = newHashTable(capacity, hashInt, compare);
    putIntoHashTable(t, 1, 6);
    putIntoHashTable(t, 2, 7);
    putIntoHashTable(t, 4, 8);
    putIntoHashTable(t, 3, 9);
    putIntoHashTable(t, 5, 10);
    for(i = 0; i <= 5; i++) {
        HashNodePtr node = getFromHashTable(t, i);
        if(node) {
            printf("key %d values %d\n", node->key, node->value);
        } else {
            printf("can find key %d\n", i);
        }
    }
    freeHashTable(t);
    return 0;
}


