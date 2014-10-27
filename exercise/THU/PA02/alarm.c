#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_from_stdin();
int next_int(int*);
int next_longlong(long long*);

#define COMPUTE(A, B, X) (B - B*X/A)

int main() {
    int n, m, i, lo, hi, mid;
    long long *ys, *xs, x, y;
    char* buf = read_from_stdin();
    next_int(&n);
    next_int(&m);
    ys = (long long*)malloc(n*sizeof(long long));
    xs = (long long*)malloc(n*sizeof(long long));
    for(i = 0; i < n; i++) {
        next_longlong(xs + i);
        next_longlong(ys + i);
    }
    buf[0] = '\0';
    for(i = 0; i < m; i++) {
        lo = 0, hi = n, mid;
        next_longlong(&x);
        next_longlong(&y);
        while(lo < hi) {
            mid = (hi + lo)>>1;
            if(y < COMPUTE(xs[mid], ys[mid], x)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        printf("%d\n", lo);
        //sprintf(buf + strlen(buf), "%d\n\0", lo);
    }
    //printf("%s", buf);
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
int next_longlong(long long *res) {
    *res = 0LL;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    while(c >= '0' && c <= '9') {
        *res = (*res)*10LL + (long long)(c - '0');
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
    *res = 0LL;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    while(c >= '0' && c <= '9') {
        *res = (*res)*10LL + (long long)(c - '0');
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
