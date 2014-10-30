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

#define CONTAINER_SIZE (16<<20)
#define BUCKET_SIZE (CONTAINER_SIZE>>4)
#define EMPTY (0L)
#define RADIX (0xfL)

long *get_buckets() {
    long* buckets = (long*)malloc(sizeof(long)*CONTAINER_SIZE);
    memset(buckets, 0L, sizeof(long)*CONTAINER_SIZE);
    return buckets;
}

void rsort(long radix, int zeros, long* buckets, long* array, int lo, int hi) {
    int len = hi - lo, i, j, k, bi[16], r;
    array += lo;
    memset(bi, 0, sizeof(int)*16);
    for(i = 0; i < len; i++) {
        r = (radix & array[i])>>zeros;
        buckets[r*BUCKET_SIZE + (bi[r]++)] = array[i];
    }
    // copy back and reset
    for(i = 0, k = 0; i < 16; i++) {
        for(j = 0; j < BUCKET_SIZE && buckets[j]; j++) {
            array[k++] = buckets[j];
            buckets[j] = 0L;
        }
        buckets += BUCKET_SIZE;
    }
}

void rsort_driver(long* array, int lo, int hi) {
    long radix = RADIX, zeros = 0, *buckets = get_buckets();
    while(radix < 0xf0000000L) {
        rsort(radix, zeros, buckets, array, lo, hi);
        radix <<= 4;
        zeros += 4;
    }
    free(buckets);
}

//********************************** quick sort ***********************************************

#define CUTOFF (3)

// swap the location of a and b
void swap(LIST_TYPE* list, int a, int b) {
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE* list, int lo, int hi) {
    int mid = (lo + hi)>>1;
    hi--;
    if(GET_X(list[lo]) > GET_X(list[mid])) {
        swap(list, lo, mid);
    }
    if(GET_X(list[lo]) > GET_X(list[hi])) {
        swap(list, lo, hi);
    }
    if(GET_X(list[mid]) > GET_X(list[hi])) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE* list, int lo, int hi) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE* list, int lo, int hi) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = GET_X(median3(list, lo, hi));
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while(GET_X(list[++i]) < pivot){}
            while(GET_X(list[--j]) > pivot){}
            if(i < j) {
                swap(list, i, j);
            } else {
                break;
            }
        }
        swap(list, i, hi - 2);
        myQsort(list, lo, i);
        myQsort(list, i + 1, hi);
    } else {
        sort3(list, lo, hi);
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

#define THRESHOLD (2000000)

int main() {
    int i, n, j;
    long x, y;
    LIST_TYPE *lights;
    long long res = 0;
    fread_buf = (char*)malloc(sizeof(char)*MAX_BUF_LEN);
    read_from_stdin();
    next_int(&n);
    lights = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++) {
        next_int(&x);
        next_int(&y);
        lights[i] = (y<<32) | x;
    }
    free(fread_buf);
    if(n > THRESHOLD) {
        rsort_driver(lights, 0, n);
    } else {
        myQsort(lights, 0, n);
    }
    res = msort(lights, 0, n);
    free(lights);
    printf("%lld", res);
    return 0;
}

