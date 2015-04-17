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
    while(key < 0) {
        key += capacity;
    }
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

int *twoSum(int numbers[], int n, int target){
    int capacity = 9973, i;
    HashTablePtr t = newHashTable(capacity, hashInt, compare);
    HashNodePtr node = NULL;
    int* res = (int*)malloc(sizeof(int)*2);
    for(i = 0; i < n; i++) {
        putIntoHashTable(t, numbers[i], i);
    }
    for(i = 0; i < n; i++) {
        node = getFromHashTable(t, target - numbers[i]);
        if(node && node->value > i) {
            res[0] = i + 1;
            res[1] = node->value + 1;
            return res;
        }
    }
    freeHashTable(t);
    return NULL;
}

int main() {
    int num[] = {2, 7, 11, 15}, num1[] = {-1, -2, -3, -4, -5}, *res;
    res = twoSum(num1, 5, -8);
    printf("%d %d\n", res[0], res[1]);
    res = twoSum(num, 4, 9);
    printf("%d %d\n", res[0], res[1]);
    return 0;
}


