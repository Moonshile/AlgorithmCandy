#include<stdlib.h>
#include<stdio.h>

//********************************** merge sort inplace **************************************

typedef int LIST_TYPE;
void reverse(LIST_TYPE*, int, int);
void shift(LIST_TYPE*, int, int, int);
void merge(LIST_TYPE*, int, int, int, int (*)(const void*, const void*));
void msort(LIST_TYPE*, int, int, int (*)(const void*, const void*));

//********************************** merge sort inplace **************************************

// reverse the range [lo, hi) of list
void reverse(LIST_TYPE* list, int lo, int hi) {
    hi--;
    while(hi > lo) {
        LIST_TYPE tmp = list[lo];
        list[lo] = list[hi];
        list[hi] = tmp;
        lo++;
        hi--;
    }
}

// shift the range [lo, hi) of list with count circularly
void shift(LIST_TYPE* list, int lo, int hi, int count) {
    int mid = hi - count;
    reverse(list, lo, mid);
    reverse(list, mid, hi);
    reverse(list, lo, hi);
}

void merge(LIST_TYPE* list, int lo, int mid, int hi, int (*cmp)(const void*, const void*)) {
    int i = lo, j = mid, old_j;
    while(i < j && j < hi){
        old_j = j;
        // i<j must be tested first
        // find the first i that greater than j
        while(i < j && (*cmp)((const void*)(list + i), (const void*)(list + j)) <= 0) {
            i++;
        }
        // j<hi must be tested first
        // find the first j that not lower than i
        while(j < hi && (*cmp)((const void*)(list + j), (const void*)(list + i)) < 0) {
            j++;
        }
        shift(list, i, j, j - old_j);
        i += j - old_j;
    }
}

// sort range [lo, hi) of list
void msort(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)) {
    if(lo + 1 < hi) {
        int mid = (lo + hi)>>1;
        msort(list, lo, mid, cmp);
        msort(list, mid, hi, cmp);
        merge(list, lo, mid, hi, cmp);
    }
}

//*************************************** test ************************************************

int compare(const void* x, const void* y) {
    return (int)(*(LIST_TYPE*)x - *(LIST_TYPE*)y);
}

int main() {
    LIST_TYPE list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1},
        {1,2,321,564,6,2135,54,321,321}
    }, i, j;
    for(i = 0; i < 4; i++) {
        msort(list[i], 0, 9, &compare);
        for(j = 0; j < 9; j++) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
