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
void reset_io();

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
    char* names;
    reset_io();
    scanf("%d %d", &n, &m);
    if(n == 0 || m == 0) {
        return 0;
    }
    tasks = (Task*)malloc(sizeof(Task)*n);
    names = (char*)malloc(sizeof(char)*n*MAX_LEN);
    memset(names, 0, sizeof(char)*n*MAX_LEN);
    for(i = 0; i < n; i++) {
        scanf("%lld %s", &(tasks[i].prio), names + i*MAX_LEN);
        tasks[i].name = names + i*MAX_LEN;
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
    free(names);
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_SIZE (10<<20)
#define OUT_BUF_SIZE (10<<20)

char inbuf[IN_BUF_SIZE];
char outbuf[OUT_BUF_SIZE];

void reset_io() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
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
