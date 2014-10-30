#include <stdio.h>
#include <stdlib.h>

char *read_from_stdin();
int next_int(int*);
char next_char();

#define MAX_COUNT (1000002)

// the last unit store the pointer top
int _stack_en[MAX_COUNT];
int _stack_en_m[MAX_COUNT];
int _stack_de[MAX_COUNT];
int _stack_de_m[MAX_COUNT];

// stack interface
void init();
int empty(int*);
void push(int*, int*, int);
int pop(int*, int*);
int top(int*);
// queap interface
void enqueap(int);
int dequeap();
int min();

int main() {
    int n, x, i;
    char ch;
    read_from_stdin();
    next_int(&n);
    init();
    for(i = 0; i < n; i++) {
        ch = next_char();
        switch(ch) {
        case 'E':
            next_int(&x);
            enqueap(x);
            break;
        case 'D':
            printf("%d\n", dequeap());
            break;
        default: // M
            printf("%d\n", min());
            break;
        }
    }
	return 0;
}

#define _POINTER(X) (X[MAX_COUNT - 1])

void init() {
    _POINTER(_stack_en) = 0;
    _POINTER(_stack_en_m) = 0;
    _POINTER(_stack_de) = 0;
    _POINTER(_stack_de_m) = 0;
}

int empty(int* stack) {
    return !(_POINTER(stack));
}

void push(int* stack, int* stack_m, int value) {
    stack[_POINTER(stack)] = value;
    if(empty(stack_m) || value < top(stack_m)) {
        stack_m[_POINTER(stack)] = value;
    } else {
        stack_m[_POINTER(stack)] = top(stack_m);
    }
    _POINTER(stack)++;
    _POINTER(stack_m)++;
}

int pop(int* stack, int* stack_m) {
    _POINTER(stack_m)--;
    return stack[--_POINTER(stack)];
}

int top(int* stack) {
    return stack[_POINTER(stack) - 1];
}

void enqueap(int value) {
    push(_stack_en, _stack_en_m, value);
}

int dequeap() {
    if(empty(_stack_de)) {
        while(!empty(_stack_en)) {
            push(_stack_de, _stack_de_m, pop(_stack_en, _stack_en_m));
        }
    }
    return pop(_stack_de, _stack_de_m);
}

int min() {
    if(!(empty(_stack_de) || empty(_stack_en))) {
        return top(_stack_de_m) <= top(_stack_en_m) ? top(_stack_de_m) : top(_stack_en_m);
    }
    if(!empty(_stack_de)) {
        return top(_stack_de_m);
    }
    return top(_stack_en_m);
}

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
