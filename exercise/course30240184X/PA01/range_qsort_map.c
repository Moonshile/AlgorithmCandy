#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int LIST_TYPE;
//****************************** fast io ******************************************************
void reset_io();
//*************************************** qsort **************************************************
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(LIST_TYPE*, int, int, int (*)(const void*, const void*));

//****************************** program ******************************************************

int compare(const void* x, const void* y) {
    return (int)(*(LIST_TYPE*)x - *(LIST_TYPE*)y);
}

#define MAX_NUM (10<<20)
#define NOT_INIT (-2)

int main(){
    int n, m, i, j, ia, ib;
    LIST_TYPE *points, a, b, *query_map;
    reset_io();
    query_map = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*MAX_NUM);
    scanf("%d %d", &n, &m);
    points = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++) {
        scanf("%d", points + i);
    }
    myQsort(points, 0, n, &compare);
    for(i = 0, j = 0; i < MAX_NUM; i++) {
        if(i == points[j]) {
            query_map[i] = j++;
        } else {
            query_map[i] = j - 1;
        }
    }
    for(i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        ia = query_map[a];
        ib = query_map[b];
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
