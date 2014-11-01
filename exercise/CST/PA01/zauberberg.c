#include <stdio.h>
#include <stdlib.h>

typedef struct __creature__ {
    int height;
    int positive;
    int negative;
} Creature;

typedef Creature LIST_TYPE;

//****************************** fast io *******************************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();

//*************************************** qsort **************************************************
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
void myQsort(LIST_TYPE*, int, int, int (*)(const void *, const void *));

//************************************** binary search **********************************************

// search e in list, with range [lo, hi)
// if e does not exist, then return the greatest index of the element that not greater than e
int bin_search(LIST_TYPE*, int, int, LIST_TYPE, int (*)(const void*, const void *));

//*************************************** program ***************************************************

int compare_height(const void *x, const void *y) {
    return ((Creature*)y)->height - ((Creature*)x)->height;
}

int main(){
    char* buf = reset_io(), ch;
    int n, h, m, i, j;
    float *phits, *pfalses;
    Creature* cs;
    next_int(&n);
    next_int(&h);
    cs = (Creature*)malloc(sizeof(Creature)*n);
    // input
    for(i = 0; i < n; i++) {
        next_int(&(cs[i].height));
        ch = next_char();
        if(ch == '+') {
            cs[i].positive ++;
        } else {
            cs[i].negative ++;
        }
    }
    // sort desc and unify
    myQsort(cs, 0, n, &compare_height);
    for(i = 0, j = 1; j < n; j++) {
        if(cs[i].height == cs[j].height) {
            cs[i].positive += cs[j].positive;
            cs[i].negative += cs[j].negative;
        } else {
            i++;
            cs[i].positive = cs[j].positive;
            cs[i].negative = cs[j].negative;
        }
    }
    // now i is count of height
    i++;
    // compute phit and pfalse
    phits = (float*)malloc(sizeof(float)*i);
    pfalses = (float*)malloc(sizeof(float)*i);
    for(j = 0; j < i; j++) {
        
    }
    free(cs);
    free(phits);
    free(pfalses);
    free(buf);
    return 0;
}

//****************************** fast io ***********************************************************
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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0' || c == '+' || c == '-')) {
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
    if((*cmp)((const void *)(list + lo), (const void *)(list + mid)) > 0) {
        swap(list, lo, mid);
    }
    if((*cmp)((const void *)(list + lo), (const void *)(list + hi)) > 0) {
        swap(list, lo, hi);
    }
    if((*cmp)((const void *)(list + mid), (const void *)(list + hi)) > 0) {
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
            while((*cmp)((const void *)(list + (++i)), (const void *)&pivot) < 0){}
            while((*cmp)((const void *)(list + (--j)), (const void *)&pivot) > 0){}
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

//************************************** binary search **********************************************

// search e in list, with range [lo, hi)
// if e does not exist, then return the greatest index of the element that not greater than e
int bin_search(LIST_TYPE *list, int lo, int hi, LIST_TYPE e, int (*cmp)(const void*, const void *)){
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        int mi = (hi + lo)>>1;
        // if e < list[mi] then search [lo, mi) else [mi+1, hi)
        // if e== list[mi], then search [mi+1, hi) until [mi+1, mi+1) and break to return mi+1-1
        if(((*cmp)((const void *)&e, (const void *)(list + mi)) < 0)) {
            hi = mi;
        } else {
            lo  = mi + 1;
        }
    }
    return --lo;
}

