#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __task__ Task;
typedef Task prioQueueType;

//****************************** prioQueue ******************************************************
void insertIntoPrioQueue(prioQueueType* pq, prioQueueType v, int* size, long long (*cmp)(const void*, const void*));
prioQueueType getTop(prioQueueType* pq);
prioQueueType deleteTop(prioQueueType* pq, int* size, long long (*cmp)(const void*, const void*));
void heapify(prioQueueType* pq, int size, long long (*cmp)(const void*, const void*));
//****************************** fast io ******************************************************
char *reset_io();
int next_int(int*);
int next_longlong(long long*);
char* next_str();

//****************************** program ******************************************************

struct __task__ {
    long long prio;
    char* name;
};

long long compare(const void* x, const void* y) {
    if(((Task*)x)->prio == ((Task*)y)->prio) {
        return strcmp(((Task*)y)->name, ((Task*)x)->name);
    } else {
        return ((Task*)y)->prio - ((Task*)x)->prio;
    }
}

#define MAX_LEN (9)

void printTask(Task t) {
    printf("%lld %s\n", t.prio, t.name);
}

int main(){
    int n, m, i;
    Task* tasks, t;
    char* buf = reset_io();
    next_int(&n);
    next_int(&m);
    if(n == 0 || m == 0) {
        return 0;
    }
    tasks = (Task*)malloc(sizeof(Task)*n);
    for(i = 0; i < n; i++) {
        next_longlong(&(tasks[i].prio));
        tasks[i].name = next_str();
    }
    heapify(tasks, n, compare);
    for(i = 0; i < m && n > 0; i++) {
        t = deleteTop(tasks, &n, compare);
        printf("%s\n", t.name);
        t.prio <<= 1;
        if(t.prio < (1LL << 32)) {
            insertIntoPrioQueue(tasks, t, &n, compare);
        }
    }
    free(tasks);
    return 0;
}

//****************************** fast io *******************************************************
//****************************** fast io *******************************************************
#define IN_BUF_LEN (50<<20)
#define OUT_BUF_SIZE (10<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
    return fread_buf;
}

int next_int(int* res) {
    long long t;
    next_longlong(&t);
    *res = (int)t;
}

// next integer, prefix blanks will be removed
int next_longlong(long long *res) {
    char c = fread_buf[fread_buf_pointer++];
    int is_pos = 1;
    while(!(c >= '0' && c <= '9' || c == '\0' || c == '-')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    if(c == '-') {
        is_pos = 0;
        c = fread_buf[fread_buf_pointer++];
    }
    *res = 0;
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    if(!is_pos) {
        *res = -*res;
    }
    return c;
}

#define IS_CHAR(a) (a >= 'a' && a <= 'z' || a >= '0' && a <= '9')

char* next_str() {
    char* res;
    while(!IS_CHAR(fread_buf[fread_buf_pointer]) && fread_buf[fread_buf_pointer] != 0) {
        fread_buf_pointer++;
    }
    res = fread_buf + fread_buf_pointer;
    while(IS_CHAR(fread_buf[fread_buf_pointer])) {
        fread_buf_pointer++;
    }
    fread_buf[fread_buf_pointer++] = 0;
    return res;
}

//****************************** prioQueue *******************************************************

#define HEAP_LEFT(i) ((i<<1) + 1)
#define HEAP_RIGHT(i) ((i<<1) + 2)
#define HEAP_PARENT(i) ((i - 1)>>1)

void percolateUp(prioQueueType* pq, int node, long long (*cmp)(const void*, const void*)) {
    prioQueueType v = pq[node];
    int i = node, j;
    while(i > 0) {
        j = HEAP_PARENT(i);
        if(cmp(pq + j, &v) < 0) {
            pq[i] = pq[j];
            i = j;
        } else {
            break;
        }
    }
    pq[i] = v;
}

void insertIntoPrioQueue(prioQueueType* pq, prioQueueType v, int* size, long long (*cmp)(const void*, const void*)) {
    pq[(*size)] = v;
    percolateUp(pq, (*size)++, cmp);
}

prioQueueType getTop(prioQueueType* pq) {
    return pq[0];
}

void percolateDown(prioQueueType* pq, int node, int size, long long (*cmp)(const void*, const void*)) {
    prioQueueType v = pq[node];
    int i = node, lc = HEAP_LEFT(i), rc = HEAP_RIGHT(i);
    while(lc < size) {
        if(rc < size && cmp(pq + lc, pq + rc) < 0 && cmp(&v, pq + rc) < 0) {
            pq[i] = pq[rc];
            i = rc;
        } else if(cmp(&v, pq + lc) < 0) {
            pq[i] = pq[lc];
            i = lc;
        } else {
            break;
        }
        lc = HEAP_LEFT(i);
        rc = HEAP_RIGHT(i);
    }
    pq[i] = v;
}

prioQueueType deleteTop(prioQueueType* pq, int* size, long long (*cmp)(const void*, const void*)) {
    prioQueueType res = pq[0];
    pq[0] = pq[--(*size)];
    percolateDown(pq, 0, *size, cmp);
    return res;
}

void heapify(prioQueueType* pq, int size, long long (*cmp)(const void*, const void*)) {
    int i = (size>>1) - 1;
    while(i >= 0) {
        percolateDown(pq, i--, size, cmp);
    }
}
