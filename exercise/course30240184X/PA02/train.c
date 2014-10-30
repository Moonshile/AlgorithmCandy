#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_LEN (20<<10<<10)
char *read_from_stdin();
int next_int(int*);

int stack_p = 0;

int my_push(int* stack, int m, int x) {
    if(stack_p >= m || stack_p < 0) {
        return -1;
    }
    stack[stack_p++] = x;
    return stack_p;
}

int my_top(int* stack) {
    return stack[stack_p - 1];
}

void my_pop() {
    --stack_p;
}

#define POP(BUF) {\
    *(--BUF) = '\n';*(--BUF) = 'p';*(--BUF) = 'o';*(--BUF) = 'p';\
}

#define PUSH(BUF) {\
    *(--BUF) = '\n';*(--BUF) = 'h';*(--BUF) = 's';*(--BUF) = 'u';*(--BUF) = 'p';\
}

int main() {
    int n, m, i, j, *out, *stack, x;
    char* buf = read_from_stdin();
    next_int(&n);
    next_int(&m);
    out = (int*)malloc(n*sizeof(int));
    stack = (int*)malloc(m*sizeof(int));
    for(i = 0; i < n; i++) {
        next_int(out + i);
    }
    buf += MAX_BUF_LEN;
    *(--buf) = '\0';
    for(i = n - 1, j = n; i >= 0; i--) {
        if(my_push(stack, m, out[i]) == -1) {
            printf("No\n");
            return 0;
        }
        POP(buf);
        while(stack_p > 0 && my_top(stack) == j) {
            my_pop();
            PUSH(buf);
            j--;
        }
    }
    free(out);
    free(stack);
    printf("%s", (stack_p == 0 ? buf : "No\n"));
    return 0;
}

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
