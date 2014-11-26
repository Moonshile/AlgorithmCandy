#include <stdio.h>
#include <stdlib.h>

//****************************** list ******************************************************
typedef int ListType;
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

//****************************** test ******************************************************

void printList(List* l) {
    Position* p = l->header->next;
    while(p != l->trailor) {
        printf("%d ", p->ele);
        p = p->next;
    }
    printf("\n");
}

int main() {
    List* l = newList();
    int n = 10, i;
    Position* p = l->header;
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
