#include <stdio.h>
#include <stdlib.h>

typedef int QSORT_TYPE;

//*************************************** qsort **************************************************
void swap(QSORT_TYPE*, int, int);
void sort3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
QSORT_TYPE median3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(QSORT_TYPE*, int, int, int (*)(const void*, const void*));

//************************************** qsort ***************************************************

#define CUTOFF (3)

// swap the location of a and b
void swap(QSORT_TYPE* list, int a, int b) {
    QSORT_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(QSORT_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    hi--;
    if(cmp(list + lo, list + mid) > 0) {
        swap(list, lo, mid);
    }
    if(cmp(list + lo, list + hi) > 0) {
        swap(list, lo, hi);
    }
    if(cmp(list + mid, list + hi) > 0) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
QSORT_TYPE median3(QSORT_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi, cmp);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(QSORT_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    int i, j;
    QSORT_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list, lo, hi, cmp);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while(cmp(list + (++i), &pivot) < 0){}
            while(cmp(list + (--j), &pivot) > 0){}
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

//********************************************** test ***********************************************

int compare(const void* x, const void* y) {
    return (int)(*(QSORT_TYPE*)x - *(QSORT_TYPE*)y);
}

int main() {
    QSORT_TYPE list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1}
    };
    int i, j;
    for(i = 0; i < 3; i++) {
        myQsort(list[i], 0, 9, &compare);
        for(j = 0; j < 9; j++) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}

