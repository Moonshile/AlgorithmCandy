#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __name__ {
    const char* s;
    int count;
} Name;
#define EMPTY_HASH_VALUE (0)
typedef Name* HashType;

//****************************** fast io ******************************************************
void reset_io();

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

//****************************** program ******************************************************

#define MAX_CAPACITY (10009)
#define MAX_STR (9)

int hashName(Name* name, int capacity) {
    return hashStr(name->s, capacity);
}

int compare(const void* x, const void* y) {
    return strcmp((*(HashType*)x)->s, (*(HashType*)y)->s);
}

int main(){
    int n, i, j, p;
    char* strs;
    HashTable* t = newHashTable(MAX_CAPACITY);
    Name* names;
    reset_io();
    strs = (char*)malloc(sizeof(char)*MAX_CAPACITY*MAX_STR);
    memset(strs, 0, sizeof(char)*MAX_CAPACITY*MAX_STR);
    names = (Name*)malloc(sizeof(Name)*MAX_CAPACITY);
    scanf("%d", &n);
    for(i = 0, j = 0; i < n; i++) {
        scanf("%s", strs + j*MAX_STR);
        names[j].s = strs + j*MAX_STR;
        names[j].count = 1;
        p = findInHashTable(t, names + j, &hashName, &compare);
        if(t->table[p]) {
            t->table[p]->count++;
        } else {
            t->table[p] = names + j;
			j++;
        }
    }
    p = 0;
    for(i = 0; i < j; i++) {
        if(names[i].count > p) {
            p = names[i].count;
            n = i;
        }
    }
    printf("%s %d\n", names[n].s, p);
    free(strs);
    free(names);
    freeHashTable(t);
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_SIZE (1<<20)
#define OUT_BUF_SIZE (1<<10)

char inbuf[IN_BUF_SIZE];
char outbuf[OUT_BUF_SIZE];

void reset_io() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}

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


