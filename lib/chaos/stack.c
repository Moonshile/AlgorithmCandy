#include <stdio.h>
#include <stdlib.h>

typedef int StackType;
#define EMPTY_STACK_VALUE (0);

//****************************** stack ******************************************************
typedef struct __stack__ {
    StackType* container;
    int top;
    int capacity;
} Stack;
Stack* newStack(int capacity);
int isEmptyStack(Stack* s);
void push(Stack* s, StackType v);
StackType pop(Stack* s);
StackType top(Stack* s);
void freeStack(Stack* s);

//****************************** stack ******************************************************

Stack* newStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->container = (StackType*)malloc(sizeof(StackType)*capacity);
    s->top = 0;
    s->capacity = capacity;
    return s;
}

int isEmptyStack(Stack* s) {
    return s->top == 0;
}

void push(Stack* s, StackType v) {
    if(s->top < s->capacity) {
        s->container[s->top++] = v;
    }
}

StackType pop(Stack* s) {
    if(s->top > 0) {
        return s->container[--(s->top)];
    }
    return EMPTY_STACK_VALUE;
}

StackType top(Stack* s) {
    return s->top > 0 ? s->container[s->top - 1] : EMPTY_STACK_VALUE;
}

void freeStack(Stack* s) {
    free(s->container);
    free(s);
}

//****************************** test ******************************************************

int main() {
    int n = 10, i;
    Stack* s = newStack(n);
    for(i = 0; i < n; i++) {
        push(s, i + 1);
    }
    push(s, -1);
    for(i = 0; i < n + 5; i++) {
        printf("%d ", pop(s));
    }
    printf("\n");
    freeStack(s);
    return 0;
}

