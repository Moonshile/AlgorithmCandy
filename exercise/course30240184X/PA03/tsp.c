#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int QueueType;
#define EMPTY_QUEUE_VALUE (0)
typedef int ListType;

//****************************** fast io ******************************************************
void reset_io();
//****************************** queue ******************************************************
typedef struct __queue__ {
    QueueType* container;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;
Queue* newQueue(int capacity);
void enqueue(Queue* q, QueueType e);
QueueType dequeue(Queue* q);
void freeQueue(Queue* q);
//****************************** list ******************************************************
typedef struct __position__ {
    ListType ele;
    struct __position__* pre;
    struct __position__* next;
} Position;
typedef struct __list__ {
    Position* header;
    Position* trailor;
} List;
List* newList();
void insertAsSuccInList(ListType v, Position* pre);
void removeFromList(Position* v);
void removeRangeFromList(Position* lo, Position* hi);
void freeList(List* l);

//****************************** program ******************************************************

int main(){
    int n, m, i, x, y, *deg, *path;
    List** table;
    Queue* q;
    Position* p;
    reset_io();
    scanf("%d %d", &n, &m);
    table = (List**)malloc(sizeof(List*)*n);
    deg = (int*)malloc(sizeof(int)*n);
    path = (int*)malloc(sizeof(int)*n);
    memset(deg, 0, sizeof(int)*n);
    memset(path, 0, sizeof(int)*n);
    q = newQueue(n);
    for(i = 0; i < n; i++) {
        table[i] = newList();
    }
    for(i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        insertAsSuccInList(y, table[x]->trailor->pre);
        deg[y]++;
    }
    for(i = 0; i < n; i++) {
        if(deg[i] == 0) {
            enqueue(q, i);
        }
    }
    while(q->size > 0) {
        x = dequeue(q);
        p = table[x]->header->next;
        while(p != table[x]->trailor) {
            deg[p->ele]--;
            if(deg[p->ele] == 0) {
                enqueue(q, p->ele);
            }
            if(path[x] + 1 > path[p->ele]) {
                path[p->ele] = path[x] + 1;
            }
            p = p->next;
        }
    }
    x = -1;
    for(i = 0; i < n; i++) {
        if(path[i] > x) {
            x = path[i];
        }
    }
    printf("%d\n", x + 1);
    for(i = 0; i < n; i++) {
        freeList(table[i]);
    }
    free(table);
    free(deg);
    free(path);
    freeQueue(q);
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
    q->container = (QueueType*)malloc(sizeof(QueueType)*capacity);
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, QueueType e) {
    if(q->size < q->capacity) {
        (q->container)[(q->rear)++] = e;
        if(q->rear >= q->capacity) {
            q->rear -= q->capacity;
        }
        (q->size)++;
    }
}

QueueType dequeue(Queue* q) {
    if(q->size > 0) {
        QueueType ret = (q->container)[(q->front)++];
        if(q->front >= q->capacity) {
            q->front -= q->capacity;
        }
        (q->size)--;
        return ret;
    }
    return EMPTY_QUEUE_VALUE;
}

void freeQueue(Queue* q) {
    free(q->container);
    free(q);
}

//****************************** list ******************************************************

List* newList() {
    List* l = (List*)malloc(sizeof(List));
    l->header = (Position*)malloc(sizeof(Position));
    l->trailor = (Position*)malloc(sizeof(Position));
    l->header->pre = 0;
    l->header->next = l->trailor;
    l->trailor->pre = l->header;
    l->trailor->next = 0;
    return l;
}

void insertAsSuccInList(ListType v, Position* pre) {
    Position* x = (Position*)malloc(sizeof(Position));
    x->ele = v;
    x->next = pre->next;
    x->pre = pre;
    pre->next->pre = x;
    pre->next = x;
}

void removeFromList(Position* v) {
    removeRangeFromList(v, v->next);
}

void removeRangeFromList(Position* lo, Position* hi) {
    if(lo != hi) {
        Position* toRm = lo, *tmp;
        hi->pre->next = 0;
        lo->pre->next = hi;
        hi->pre = lo->pre;
        while(toRm) {
            tmp = toRm;
            toRm = toRm->next;
            free(tmp);
        }
    }
}

void freeList(List* l) {
    removeRangeFromList(l->header->next, l->trailor);
    free(l->header);
    free(l->trailor);
    free(l);
}
