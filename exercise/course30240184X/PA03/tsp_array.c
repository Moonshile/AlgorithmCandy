#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __edge__ {
    int s;
    int d;
} Edge;

//****************************** fast io ******************************************************
void reset_io();
//****************************** queue ******************************************************
typedef int QueueType;
typedef struct __queue__ {
    QueueType* queue;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;
Queue* newQueue(int capacity);
void enqueue(Queue* q, QueueType e);
QueueType dequeue(Queue* q);
//*************************************** qsort **************************************************
typedef Edge LIST_TYPE;
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(LIST_TYPE*, int, int, int (*)(const void*, const void*));

//****************************** program ******************************************************

int compare(const void* x, const void* y) {
    return ((Edge*)x)->s - ((Edge*)y)->s;
}

int main(){
    int n, m, i, x, y, d, *deg, *path, *entry;
    Edge* table;
    Queue* q;
    reset_io();
    scanf("%d %d", &n, &m);
    table = (Edge*)malloc(sizeof(Edge)*m);
    deg = (int*)malloc(sizeof(int)*n);
    path = (int*)malloc(sizeof(int)*n);
    entry = (int*)malloc(sizeof(int)*n);
    memset(deg, 0, sizeof(int)*n);
    memset(path, 0, sizeof(int)*n);
    memset(entry, 0, sizeof(int)*n);
    q = newQueue(n);
    for(i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        table[i].s = x;
        table[i].d = y;
        deg[y]++;
    }
    // sort edges
    myQsort(table, 0, m, &compare);
    // init entry
    // x as current edge
    x = -1;
    for(i = 0; i < m; i++) {
        // edge which has a new source
        if(x != table[i].s) {
            x = table[i].s;
            entry[x] = i;
        }
    }
    // decide tsp
    for(i = 0; i < n; i++) {
        if(deg[i] == 0) {
            enqueue(q, i);
        }
    }
    while(q->size > 0) {
        x = dequeue(q);
        y = entry[x];
        while(y < m && table[y].s == x) {
            d = table[y].d;
            deg[d]--;
            if(deg[d] == 0) {
                enqueue(q, d);
            }
            if(path[x] + 1 > path[d]) {
                path[d] = path[x] + 1;
            }
            y++;
        }
    }
    // find max
    x = -1;
    for(i = 0; i < n; i++) {
        if(path[i] > x) {
            x = path[i];
        }
    }
    printf("%d\n", x + 1);
    free(table);
    free(deg);
    free(path);
    free(entry);
    free(q->queue);
    free(q);
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

//****************************** queue ******************************************************

Queue* newQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->queue = (QueueType*)malloc(sizeof(QueueType)*capacity);
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, QueueType e) {
    if(q->size < q->capacity) {
        (q->queue)[(q->rear)++] = e;
        if(q->rear >= q->capacity) {
            q->rear -= q->capacity;
        }
        (q->size)++;
    }
}

#define DEFAULT_QELE (-1)

QueueType dequeue(Queue* q) {
    if(q->size > 0) {
        QueueType ret = (q->queue)[(q->front)++];
        if(q->front >= q->capacity) {
            q->front -= q->capacity;
        }
        (q->size)--;
        return ret;
    }
    return DEFAULT_QELE;
}

//************************************** qsort ***************************************************

#define CUTOFF (3)

// swap the location of a and b
void swap(LIST_TYPE* list, int a, int b) {
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    hi--;
    if((*cmp)((const void*)(list + lo), (const void*)(list + mid)) > 0) {
        swap(list, lo, mid);
    }
    if((*cmp)((const void*)(list + lo), (const void*)(list + hi)) > 0) {
        swap(list, lo, hi);
    }
    if((*cmp)((const void*)(list + mid), (const void*)(list + hi)) > 0) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi, cmp);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list, lo, hi, cmp);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while((*cmp)((const void*)(list + (++i)), (const void*)&pivot) < 0){}
            while((*cmp)((const void*)(list + (--j)), (const void*)&pivot) > 0){}
            if(i < j) {
                swap(list, i, j);
            } else {
                break;
            }
        }
        swap(list, i, hi - 2);
        myQsort(list, lo, i, cmp);
        myQsort(list, i + 1, hi, cmp);
    } else {
        sort3(list, lo, hi, cmp);
    }
}
