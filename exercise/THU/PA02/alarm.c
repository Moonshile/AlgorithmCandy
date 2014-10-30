#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int DATATYPE;

char *reset_io();
int next_int(int*);
int next_number(DATATYPE*);

#define COMPUTE(A, B, X) ((long)B - (long)B*(long)X/(long)A)

int main() {
    int n, m, i, lo, hi, mid;
    DATATYPE *ys, *xs, x, y;
    char* buf = reset_io();
    next_int(&n);
    next_int(&m);
    ys = (DATATYPE*)malloc(n*sizeof(DATATYPE));
    xs = (DATATYPE*)malloc(n*sizeof(DATATYPE));
    for(i = 0; i < n; i++) {
        next_number(xs + i);
        next_number(ys + i);
    }
    buf[0] = '\0';
    for(i = 0; i < m; i++) {
        lo = 0, hi = n, mid;
        next_number(&x);
        next_number(&y);
        while(lo < hi) {
            mid = (hi + lo)>>1;
            if((long)y < COMPUTE(xs[mid], ys[mid], x)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        printf("%d\n", lo);
    }
    return 0;
}

//----------------------------- my libs ----------------------------------------


#define IN_BUF_LEN (100<<10<<10)
#define OUT_BUF_SIZE (10<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_number(DATATYPE *res) {
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + (DATATYPE)(c - '0');
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
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
