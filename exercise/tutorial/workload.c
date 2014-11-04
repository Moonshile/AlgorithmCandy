#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ******************************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();
int next_str(char*);

#define MAX (200000)

// dynamic processing
// for matrix m[N*N], its min total load is
// f(m) = min{ a(i) | a(i) = m[N - 1, i] + f(m'(i)), and m'(i) is the (N-1)*(N-1) sub-matrix without row (N - 1) and colomn i of matrix m }
// HOWEVER, you should always remember that each m'(i) also has their own sub-matrices

int combinatorial(n, i) {
    if(i > (n>>1)) {
        return combinatorial(n, n - i);
    } else {
        int res = 1, tmp = 1, j;
        for(j = 0; j < i; j++) {
            res *= n - j;
        }
        for(j = 2; j <= i; j++) {
            tmp *= j;
        }
        return res/tmp;
    }
}

// denotes key of m as [0, 1, 2, ..., N - 1]
//     e.g., m[5*5] has key [0, 1, 2, 3, 4]
// then m'(i) has key [0, 1, 2, ..., i - 1, i + 1, ..., N - 1]
//     e.g., m'(0) has key [1, 2, 3, 4]
// and if m''(i) is sub-matrix of m'(0), then m''(1) has key [2, 3, 4]
// NOTE that m'(0) has NO sub-matrix as m''(0)!!!
//
// But how to store these keys and use them to find the value ?
// As known, there's at most a 15*15 matrix, so maximum lenght of keys is 15
// and the maximum value of a key is also 15, which can be represented as 4
// bit, not than a long long type has size 8 byte, which is 16*4bit! So we 
// can store the keys into a long long type variable!

typedef struct __tload__ {
    long long key;
    int value;
} TLoad;

long long convertKeys(int* keys, int k) {
    long long res = 0LL;
    int i;
    for(i = 0; i < k; i++) {
        res <<= 4;
        res |= keys[i];
    }
    return res;
}

long long genKeys(int* prekeys, int k, int n) {
    if()
}

int find_min_k(int* arr, int k, int n) {
    int ret = MAX, i;
    for(i = 0; i < n; i++) {
        if(i != k && arr[i] < ret) {
            ret = arr[i];
        }
    }
    return ret;
}

int main(){
    char* buf = reset_io();
    int n, i, j, *iloads, **tloads, *mins;
    next_int(&n);
    iloads = (int*)malloc(sizeof(int)*n*n);
    tloads = (int*)malloc(sizeof(int)*n*n);
    mins = (int*)malloc(sizeof(int)*n*n);
    // read input
    for(i = 0; i < n*n; i++) {
        next_int(iloads + i);
    }
    // total loads of line 0
    for(i = 0; i < n; i++) {
        tloads[i] = iloads[i];
    }
    // min signature of line 0
    for(i = 0; i < n; i++) {
        mins[i] = find_min_k(tloads, i, n);
    }
    // total loads and min signature of other lines
    for(i = 1; i < n; i++) {
        // total loads
        for(j = 0; j < n; j++) {
            int index = i*n + j;
            tloads[index] = iloads[index] + mins[index - n];
        }
        // min signature
        for(j = 0; j < n; j++) {
            int index = i*n + j;
            mins[index] = find_min_k(tloads + i*n, j, n);
        }
    }
    printf("%d\n", find_min_k(tloads + i*(n - 1), -1, n));
    free(buf);
    return iloads[24];
}

//****************************** fast io *******************************************************
#define IN_BUF_LEN (1<<20)
#define OUT_BUF_SIZE (1<<10)

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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

int next_str(char *buf) {
    int i = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        c = fread_buf[fread_buf_pointer++];
    }
    while(c != '\n' && c != '\0') {
        buf[i] = fread_buf[fread_buf_pointer++];
        c = buf[i++];
    }
    return c;
}
