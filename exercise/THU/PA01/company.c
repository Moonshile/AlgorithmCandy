#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_from_stdin();
int next_int(int*);
char next_char();

#define MAX_N (10000000)
#define MAX_M (1000000)

int code[MAX_N];

int main() {
    int res = 0, n, m, i, closed = 0, staff, c, num = 0;
    char ch;
    read_from_stdin();
    next_int(&n);
    next_int(&m);
    // init of code
    memset(code, -1, n*sizeof(int));
    // handler input
    for(i = 0; i < m; i++) {
        ch = next_char();
        switch(ch) {
        case 'I':
            next_int(&staff);
            staff--;
            next_int(&c);
            // if closed, num = 0; else if staff is already in, num  = num, else increase num
            num = closed ? 0 : (code[staff] == -1 ? num + 1 : num);
            code[staff] = c;
            break;
        case 'O':
            next_int(&staff);
            staff--;
            // if closed, num = 0; else if staff is already out, num  = num, else decrease num
            num = closed ? 0 : (code[staff] == -1 ? num : num - 1);
            code[staff] = -1;
            break;
        case 'C':
            closed = 1;
            num = 0;
            break;
        case 'N':
            res += num;
            break;
        default: // Q
            next_int(&staff);
            staff--;
            res += closed ? -1 : code[staff];
        }
    }
    printf("%d\n", res);
    return 0;
}

//----------------------------- my libs ----------------------------------------


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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
