#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ******************************************************
void reset_io();

//****************************** program ******************************************************

#define MAX_LEN (20010)

char stack_left[MAX_LEN];
char stack_right[MAX_LEN];
int left_p = 0, right_p = MAX_LEN - 1;

void left_push(char c) {
    stack_left[left_p++] = c;
}

char left_pop() {
    return stack_left[--left_p];
}

void right_push(char c) {
    stack_right[right_p--] = c;
}

char right_pop() {
    return stack_right[++right_p];
}

void insert(int i, char c) {
    int j;
    for(j = left_p; j < i; j++) {
        left_push(right_pop());
    }
    for(j = left_p; j > i; j--) {
        right_push(left_pop());
    }
    left_push(c);
}

void eliminate() {
    int len = 3, old_lp, old_rp;
    char c;
    while(len >= 3) {
        c = stack_left[left_p - 1];
        old_lp = left_p;
        old_rp = right_p;
        len = 0;
        while(left_p > 0 && stack_left[left_p - 1] == c) {
            left_p--;
            len++;
        }
        while(stack_right[right_p + 1] == c) {
            right_p++;
            len++;
        }
    }
    left_p = old_lp;
    right_p = old_rp;
}

void print() {
    int empty = left_p == 0 && right_p == MAX_LEN - 3;
    stack_left[left_p] = '\0';
    printf("%s%s", empty ? "-" : stack_left, stack_right + right_p + 1);
}

int main(){
    char ch;
    int n, i, index;
    reset_io();
    right_push('\0');
    right_push('\n');
    ch = getchar();
    while(!(ch == '\n' || ch == '\r')) {
        if(ch >= 'A' && ch <= 'Z') {
            left_push(ch);
        }
        ch = getchar();
    }
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d", &index);
        ch = getchar();
        while(!(ch >= 'A' && ch <= 'Z')) {
            ch = getchar();
        }
        insert(index, ch);
        eliminate();
        print();
    }
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_SIZE (1<<20)
#define OUT_BUF_SIZE (1<<20)

char inbuf[IN_BUF_SIZE];
char outbuf[OUT_BUF_SIZE];

void reset_io() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}
