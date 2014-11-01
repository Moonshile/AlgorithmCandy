#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);

#define MAX_COUNT (10001)

int _top = 0;
int _stack[MAX_COUNT];

int empty() {
    return _top == 0;
}

void push(int value) {
    _stack[_top++] = value;
}

int pop() {
    return _stack[--_top];
}

int top() {
    return _stack[_top - 1];
}

// return its index
int find_max(int* array, int base, int n) {
    if(n > 0) {
        int ret = base, i;
        for(i = base + 1; i < n; i++) {
            ret = array[i] > array[ret] ? i : ret;
        }
        return ret;
    }
    return -1;
}

int main(){
    char* buf = reset_io();
    int n, i, j, *nums;
    next_int(&n);
    nums = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++) {
        next_int(nums + i);
    }
    for(i = 0; i < n; ) {
        int old_i = i;
        i = find_max(nums, i, n) + 1;
        while(!empty() && top() >= nums[i - 1]) {
            printf("%d ", pop());
        }
        for(j = old_i; j < i; j++) {
            push(nums[j]);
        }
    }
    while(!empty()) {
        printf("%d ", pop());
    }
    free(buf);
    return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (10<<20)
#define OUT_BUF_SIZE (10<<20)

char *fread_buf;
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    fread_buf = (char*)malloc(sizeof(char)*IN_BUF_LEN);
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
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
