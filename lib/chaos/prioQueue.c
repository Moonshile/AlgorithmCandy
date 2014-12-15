#include <stdio.h>
#include <stdlib.h>

typedef int prioQueueType;

//****************************** prioQueue ******************************************************
void insertIntoPrioQueue(prioQueueType* pq, prioQueueType v, int* size, int (*cmp)(const void*, const void*));
prioQueueType getMax(prioQueueType* pq);
prioQueueType deleteMax(prioQueueType* pq, int* size, int (*cmp)(const void*, const void*));
void heapify(prioQueueType* pq, int size, int (*cmp)(const void*, const void*));

//****************************** prioQueue *******************************************************

#define HEAP_LEFT(i) ((i<<1) + 1)
#define HEAP_RIGHT(i) ((i<<1) + 2)
#define HEAP_PARENT(i) ((i - 1)>>1)

void percolateUp(prioQueueType* pq, int node, int (*cmp)(const void*, const void*)) {
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

void insertIntoPrioQueue(prioQueueType* pq, prioQueueType v, int* size, int (*cmp)(const void*, const void*)) {
    pq[(*size)] = v;
    percolateUp(pq, (*size)++, cmp);
}

prioQueueType getMax(prioQueueType* pq) {
    return pq[0];
}

void percolateDown(prioQueueType* pq, int node, int size, int (*cmp)(const void*, const void*)) {
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

prioQueueType deleteMax(prioQueueType* pq, int* size, int (*cmp)(const void*, const void*)) {
    prioQueueType res = pq[0];
    pq[0] = pq[--(*size)];
    percolateDown(pq, 0, *size, cmp);
    return res;
}

void heapify(prioQueueType* pq, int size, int (*cmp)(const void*, const void*)) {
    int i = (size>>1) - 1;
    while(i >= 0) {
        percolateDown(pq, i--, size, cmp);
    }
}

//****************************** test ******************************************************

int compare(const void* x, const void* y) {
    return *(prioQueueType*)x - *(prioQueueType*)y;
}

int printHeap(prioQueueType* h, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");
}

int main(){
    int x[] = {1, 2, 3, 4, 5};
    int y[] = {0, 0, 0, 0, 0};
    int z[] = {1, 2, 10};
    int size = 0, i;
    for(i = 0; i < 5; i++) {
        insertIntoPrioQueue(y, x[i], &size, compare);
        printHeap(y, size);
    }
    for(i = 0; i < 5; i++) {
        deleteMax(y, &size, compare);
        printHeap(y, size);
    }
    size = 3;
    heapify(z, size, compare);
    printHeap(z, size);
    return 0;
}

