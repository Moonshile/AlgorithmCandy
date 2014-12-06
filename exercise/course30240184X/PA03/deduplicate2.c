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
void reset_io(char* fread_buf, int in_len);
char* next_int(char* fread_buf, int *res);
int next_str(char *fread_buf);

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

#define MAX_CAPACITY (600053>>1)
#define MAX_STR (41)

int hashName(Name* name, int capacity) {
    return hashStr(name->s, capacity);
}

int compare(const void* x, const void* y) {
    return strcmp((*(HashType*)x)->s, (*(HashType*)y)->s);
}

int main(){
    int n, i, p, len = MAX_CAPACITY*MAX_STR;
    char* strs = (char*)malloc(sizeof(char)*len), *buf = strs;
    HashTable* t = newHashTable(MAX_CAPACITY);
    Name* names = (Name*)malloc(sizeof(Name)*MAX_CAPACITY);
    reset_io(buf, len);
    buf = next_int(buf, &n);
    len = 0;
    for(i = 0; i < n; i++) {
        len = next_str(buf);
        names[i].s = buf;
        buf += len;
        names[i].count = 1;
        p = findInHashTable(t, names + i, hashName, compare);
        if(t->table[p] && t->table[p]->count == 1) {
            printf("%s\n", t->table[p]->s);
            t->table[p]->count++;
        } else if(!t->table[p]) {
            t->table[p] = names + i;
        }
    }
    free(strs);
    free(names);
    freeHashTable(t);
    return 0;
}

//****************************** fast io *******************************************************
#define OUT_BUF_SIZE (1<<20)

char outbuf[OUT_BUF_SIZE];

void reset_io(char* fread_buf, int in_len) {
    int len = fread(fread_buf, sizeof(char), in_len, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}

// next integer, prefix blanks will be removed
char* next_int(char* fread_buf, int *res) {
    char c = *(fread_buf++);
    while(!(c >= '0' && c <= '9' || c == '\0' || c == '-')) {
        c = *(fread_buf++);
    }
    *res = 0;
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = *(fread_buf++);
    }
    while(!(c >= 'a' && c <= 'z')) {
        *(fread_buf - 1) = 0;
        c = *(fread_buf++);
    }
    return --fread_buf;
}

int next_str(char *fread_buf) {
    int ret = 0;
    char c = fread_buf[ret++];
    while(c >= 'a' && c <= 'z') {
        c = fread_buf[ret++];
    }
    while(!(c >= 'a' && c <= 'z') && c != 0) {
        fread_buf[ret - 1] = 0;
        c = fread_buf[ret++];
    }
    return ret - 1;
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


