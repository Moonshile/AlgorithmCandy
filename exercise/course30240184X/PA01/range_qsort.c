#include <stdio.h>
#include <stdlib.h>

typedef int LIST_TYPE;
//****************************** fast io ******************************************************
void reset_io();
//*************************************** qsort **************************************************
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(LIST_TYPE*, int, int, int (*)(const void*, const void*));
//************************************** binary search **********************************************
int bin_search(LIST_TYPE*, int, int, LIST_TYPE, int (*)(const void*, const void*));

//****************************** program ******************************************************

int compare(const void* x, const void* y) {
    return (int)(*(LIST_TYPE*)x - *(LIST_TYPE*)y);
}

int main(){
    int n, m, i, ia, ib;
    LIST_TYPE *points, a, b;
    reset_io();
    scanf("%d %d", &n, &m);
    points = (int*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++) {
        scanf("%d", points + i);
    }
    myQsort(points, 0, n, &compare);
    for(i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        ia = bin_search(points, 0, n, a, &compare);
        ib = bin_search(points, 0, n, b, &compare);
        ia = ia < 0 ? 0 : (a == points[ia] ? ia : ia + 1);
        printf("%d\n", ia > ib ? 0 : ib - ia + 1);
    }
    free(points);
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_SIZE (10<<20)
#define OUT_BUF_SIZE (10<<20)

char inbuf[IN_BUF_SIZE];
char outbuf[OUT_BUF_SIZE];

void reset_io() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}

//************************************** qsort ***************************************************

#define CUTOFF (3)

// swap the location of a and b
void swap(LIST_TYPE* list, int a, int b) {
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    hi--;
    if((*cmp)((const void*)(list + lo), (const void*)(list + mid)) > 0) {
        swap(list, lo, mid);
    }
    if((*cmp)((const void*)(list + lo), (const void*)(list + hi)) > 0) {
        swap(list, lo, hi);
    }
    if((*cmp)((const void*)(list + mid), (const void*)(list + hi)) > 0) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi, cmp);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list, lo, hi, cmp);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while((*cmp)((const void*)(list + (++i)), (const void*)&pivot) < 0){}
            while((*cmp)((const void*)(list + (--j)), (const void*)&pivot) > 0){}
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
int bin_search(LIST_TYPE* list, int lo, int hi, LIST_TYPE e, int (*cmp)(const void*, const void*)){
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        int mi = (hi + lo)>>1;
        // if e < list[mi] then search [lo, mi) else [mi+1, hi)
        // if e== list[mi], then search [mi+1, hi) until [mi+1, mi+1) and break to return mi+1-1
        if(((*cmp)((const void*)&e, (const void*)(list + mi)) < 0)) {
            hi = mi;
        } else {
            lo  = mi + 1;
        }
    }
    return --lo;
}
