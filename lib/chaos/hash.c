#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY (0)
#define DELETED (1)
#define BUSY (2)

#define FALSE (0)
#define TRUE (1)

typedef int KeyType;
typedef int ValueType;

//*************************************** hash **************************************************
typedef struct __hash_node__ {
    KeyType key;
    ValueType value;
    int status;
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
void putIntoHashTable(HashTablePtr t, KeyType key, ValueType v);
HashNodePtr getFromHashTable(HashTablePtr t, KeyType key);
void removeFromHashTable(HashTablePtr t, KeyType key);
void freeHashTable(HashTablePtr t);

//*************************************** hash **************************************************

HashTablePtr newHashTable(int capacity, 
    int (*hash)(KeyType, int), 
    int (*cmp)(const void*, const void*)) {
    HashTablePtr t = (HashTablePtr)malloc(sizeof(HashTable));
    int i;
    t->table = (HashNodePtr)malloc(sizeof(HashNode)*capacity);
    for(i = 0; i < capacity; i++) {
        t->table[i].status = EMPTY;
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

HashNodePtr findInHashTable(HashTablePtr t, KeyType key, int for_insert) {
    int p = t->hash(key, t->capacity), collision = 0;
    while(t->table[p].status == BUSY && t->cmp(&(t->table[p].key), &key) != 0
        || (for_insert ? FALSE : t->table[p].status == DELETED)) {
        // (x+1)^2 = x^2 + 2(x+1) - 1
        p += ((++collision)<<1) - 1;
        if(p >= t->capacity) {
            p -= t->capacity;
        }
    }
    return t->table + p;
}

void putIntoHashTable(HashTablePtr t, KeyType key, ValueType v) {
    HashNodePtr node = findInHashTable(t, key, TRUE);
    node->key = key;
    node->value = v;
    node->status = BUSY;
}

HashNodePtr getFromHashTable(HashTablePtr t, KeyType key) {
    HashNodePtr node = findInHashTable(t, key, FALSE);
    if(node->status != BUSY) {
        return NULL;
    }
    return node;
}

void removeFromHashTable(HashTablePtr t, KeyType key) {
    HashNodePtr node = getFromHashTable(t, key);
    if(node) {
        node->status = DELETED;
    }
}

void freeHashTable(HashTablePtr t) {
    free(t->table);
    free(t);
}

//*************************************** test **************************************************

int compare(const void* x, const void* y) {
    return *(KeyType*)x - *(KeyType*)y;
}

void printNode(HashNodePtr node) {
    const char* info[] = {"EMPTY", "DELETED", "BUSY"};
    printf("%d %s, ", node->value, info[node->status]);
}

void printHashTable(HashTablePtr t) {
    int i;
    printf("table:\n");
    for(i = 0; i < t->capacity; i++) {
        printNode(t->table + i);
    }
    printf("\b\b\n");
}

int main() {
    int capacity = 11, i;
    HashTablePtr t = newHashTable(capacity, hashInt, compare);
    HashNodePtr node;
    putIntoHashTable(t, 1, 1);
    putIntoHashTable(t, 2, 2);
    putIntoHashTable(t, 3, 3);
    putIntoHashTable(t, 4, 4);
    putIntoHashTable(t, 5, 5);
    printHashTable(t);
    for(i = 0; i <= 5; i++) {
        HashNodePtr node = getFromHashTable(t, i);
        if(node) {
            printf("key %d values %d\n", node->key, node->value);
        } else {
            printf("can find key %d\n", i);
        }
    }
    removeFromHashTable(t, 2);
    removeFromHashTable(t, 3);
    printHashTable(t);
    putIntoHashTable(t, 2, 2);
    putIntoHashTable(t, 13, 13);
    putIntoHashTable(t, 24, 24);
    printHashTable(t);
    removeFromHashTable(t, 2);
    printHashTable(t);
    node = getFromHashTable(t, 13);
    printf("key %d values %d\n", node->key, node->value);
    node = getFromHashTable(t, 24);
    printf("key %d values %d\n", node->key, node->value);
    putIntoHashTable(t, 35, 35);
    printHashTable(t);
    freeHashTable(t);
    return 0;
}


