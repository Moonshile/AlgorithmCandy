#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN (100<<10<<10)

char *fread_buf;
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(long *res) {
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

typedef long LIST_TYPE;

#define LOW32 (0xffffffffL)
#define HIGH32 (0xffffffff00000000L)
#define GET_X(YX) (YX&LOW32)
// YX1 > YX2 iff Y1 > Y2
#define GET_Y(YX) (YX)

#define MAX_X (100000000)

//***************************** radix sort x *************************************************

// map size must be prime
#define CONTAINER_SIZE (8<<20)
#define EMPTY (0L)
#define RADIX (0x0f000000)

long _bucket[CONTAINER_SIZE], _bucketHelp[CONTAINER_SIZE];

#define COPY_TO_H(i) {\
    for(i = 0; i < CONTAINER_SIZE; _bucketHelp[i] = _bucket[i++]);\
    memset(_bucket, 0, sizeof(long)*CONTAINER_SIZE);\
}

void sort() {
    int radix = RADIX >> 4, i, j, bucket_c = 0x10, num_in_every_bucket = CONTAINER_SIZE >> 4, base, addr;
    while(radix) {
        COPY_TO_H(i);
        for(i = 0; i < bucket_c; i++) {
            base = i*num_in_every_bucket;
            for(j = 0; j < num_in_every_bucket; j++) {
                addr = base | j;
                if(_bucketHelp[addr]) {
                    switch(radix&_bucket[addr]) {
                    case 0x0:
                        
                        break;
                    }
                }
            }
        }
        radix >>= 4;
        bucket_c <<= 4;
        num_in_every_bucket >>= 4;
    }
}

//********************************** merge sort ***********************************************

// merge two sub lists that have been sorted
long long merge(LIST_TYPE* list, LIST_TYPE* tmp, int lo, int mi, int hi) {
    LIST_TYPE* a = list + lo, *b = tmp + lo, *c = list + mi;
    int len_b = mi - lo, len_c = hi - mi, i, j, k;
    long long res = 0LL;
    // copy b to its temporary location
    for(i = 0; i < len_b; b[i] = a[i++]);
    // the test should be j < len_b && k < len_c, but in fact, 
    // k < len_c is always tested before copy c, so this condition could be omitted
    for(i = 0, j = 0, k = 0; j < len_b; ) {
        // the following two if clause could be exchanged,
        // but will produce extra iterations in this loop
        
        // c hasn't been copied, and c[k] is lower than b[j]
        if(k < len_c && GET_Y(c[k]) < GET_Y(b[j])) {
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || GET_Y(b[j]) <= GET_Y(c[k])) {
            a[i++] = b[j++];
            res += len_c - k;
        }
    }
    return res;
}

// act merge sort
long long msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int lo, int hi) {
    if(lo + 1 < hi) {
        int mid = (lo + hi)>>1;
        long long a = msort_do(list, tmp, lo, mid);
        long long b = msort_do(list, tmp, mid, hi);
        long long x = merge(list, tmp, lo, mid, hi);
        return a + b + x;
    }
    return 0LL;
}

// merge sort driver, sort range [lo, hi) of list
long long msort(LIST_TYPE *list, int lo, int hi) {
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(hi - lo));
    long long res = msort_do(list, tmp, lo, hi);
    free(tmp);
    return res;
}

int main() {
    int i, n, j;
    long x, y;
    LIST_TYPE *lights;
    long long res = 0;
    fread_buf = (char*)malloc(sizeof(char)*MAX_BUF_LEN);
    read_from_stdin();
    next_int(&n);
    init_map();
    for(i = 0; i < n; i++) {
        next_int(&x);
        next_int(&y);
        insert((y<<32) | x);
    }
    free(fread_buf);
    lights = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    put_to_array(lights);
    res = msort(lights, 0, n);
    free(lights);
    printf("%lld", res);
    return 0;
}

