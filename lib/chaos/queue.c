#include <stdio.h>
#include <stdlib.h>


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

//************************************ test *********************************************

int main() {
    int n = 10, i;
    Queue* q = newQueue(n);
    for(i = 0; i < n; i++) {
        enqueue(q, i);
    }
    enqueue(q, 100);
    for(i = 0; i < n; i++) {
        printf("%d ", dequeue(q));
    }
    printf("%d ", dequeue(q));
    return 0;
}
