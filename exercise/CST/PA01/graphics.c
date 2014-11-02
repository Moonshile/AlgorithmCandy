#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DATATYPE;

char *reset_io();
int next_int(int*);
int next_number(DATATYPE*);

//*************************************** qsort **************************************************

typedef DATATYPE LIST_TYPE;
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
void myQsort(LIST_TYPE*, int, int, int (*)(const void *, const void *));

#define COMPUTE(A, B, X) ((long)B - (long)B*(long)X/(long)A)

int compare(const void *x, const void *y) {
    return (int)((long)x - (long)y);
}

int main() {
    int n, m, i, lo, hi, mid;
    DATATYPE *ys, *xs, x, y;
    char* buf = reset_io();
    next_int(&n);
    ys = (DATATYPE*)malloc(n*sizeof(DATATYPE));
    xs = (DATATYPE*)malloc(n*sizeof(DATATYPE));
    for(i = 0; i < n; i++) {
        next_number(xs + i);
    }
    for(i = 0; i < n; i++) {
        next_number(ys + i);
    }
    //sort
    myQsort(xs, 0, n, &compare);
    myQsort(ys, 0, n, &compare);
    next_int(&m);
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
    free(ys);
    free(xs);
    free(buf);
    return 0;
}

//----------------------------- my libs ----------------------------------------


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

//************************************** qsort ***************************************************

#define CUTOFF (3)

// swap the location of a and b
void swap(LIST_TYPE *list, int a, int b) {
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int mid = (lo + hi)>>1;
    hi--;
    if((*cmp)((const void *)list[lo], (const void *)list[mid]) > 0) {
        swap(list, lo, mid);
    }
    if((*cmp)((const void *)list[lo], (const void *)list[hi]) > 0) {
        swap(list, lo, hi);
    }
    if((*cmp)((const void *)list[mid], (const void *)list[hi]) > 0) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi, cmp);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list, lo, hi, cmp);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while((*cmp)((const void *)list[++i], (const void *)pivot) < 0){}
            while((*cmp)((const void *)list[--j], (const void *)pivot) > 0){}
            if(i < j) {
                swap(list, i, j);
            } else {
                break;
            }
        }
        swap(list, i, hi - 2);
        myQsort(list, lo, i, cmp);
        myQsort(list, i + 1, hi, cmp);
    } else {
        sort3(list, lo, hi, cmp);
    }
}
