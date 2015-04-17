#include <stdio.h>
#include <stdlib.h>

typedef int ListType;

//****************************** list ******************************************************
typedef struct __position__ {
    ListType ele;
    struct __position__* pre;
    struct __position__* next;
} Position, *PositionPtr;
typedef struct __list__ {
    PositionPtr header;
    PositionPtr trailor;
} List, *ListPtr;
ListPtr newList();
void insertAsSuccInList(ListType v, PositionPtr pre);
void removeFromList(PositionPtr v);
void removeRangeFromList(PositionPtr lo, PositionPtr hi);
void freeList(ListPtr l);

//****************************** list ******************************************************

ListPtr newList() {
    ListPtr l = (ListPtr)malloc(sizeof(List));
    l->header = (PositionPtr)malloc(sizeof(Position));
    l->trailor = (PositionPtr)malloc(sizeof(Position));
    l->header->pre = 0;
    l->header->next = l->trailor;
    l->trailor->pre = l->header;
    l->trailor->next = 0;
    return l;
}

void insertAsSuccInList(ListType v, PositionPtr pre) {
    PositionPtr x = (PositionPtr)malloc(sizeof(Position));
    x->ele = v;
    x->next = pre->next;
    x->pre = pre;
    pre->next->pre = x;
    pre->next = x;
}

void removeFromList(PositionPtr v) {
    removeRangeFromList(v, v->next);
}

void removeRangeFromList(PositionPtr lo, PositionPtr hi) {
    if(lo != hi) {
        PositionPtr toRm = lo, tmp;
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

void freeList(ListPtr l) {
    removeRangeFromList(l->header->next, l->trailor);
    free(l->header);
    free(l->trailor);
    free(l);
}

//****************************** test ******************************************************

void printList(ListPtr l) {
    PositionPtr p = l->header->next;
    while(p != l->trailor) {
        printf("%d ", p->ele);
        p = p->next;
    }
    printf("\n");
}

int main() {
    ListPtr l = newList();
    int n = 10, i;
    PositionPtr p = l->header;
    for(i = 0; i < n; i++) {
        insertAsSuccInList(i, l->trailor->pre);
    }
    printList(l);
    p = l->header->next;
    for(i = 0; i < n/2; i++) {
        removeFromList(p);
        p = l->header->next;
    }
    printList(l);
    removeRangeFromList(l->header->next, l->trailor);
    printList(l);
    freeList(l);
    return 0;
}
