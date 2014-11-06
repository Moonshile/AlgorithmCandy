#include <stdio.h>
#include <stdlib.h>

//*************************************** qsort **************************************************
typedef int LIST_TYPE;
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(LIST_TYPE*, int, int, int (*)(const void*, const void*));


//********************************************** test ***********************************************

int compare(const void* x, const void* y) {
    return (int)(*(LIST_TYPE*)x - *(LIST_TYPE*)y);
}

int main() {
    LIST_TYPE list[][9] = {
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
