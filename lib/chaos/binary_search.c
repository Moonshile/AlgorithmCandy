#include <stdio.h>
#include <stdlib.h>

typedef int BSEARCH_TYPE;

//************************************** binary search **********************************************
int bin_search(BSEARCH_TYPE*, int, int, BSEARCH_TYPE, int (*)(const void*, const void*));


//***************************************** test ********************************************************

int compare(const void* a, const void* b){
    return (int)(*(BSEARCH_TYPE*)a - *(BSEARCH_TYPE*)b);
}

int main(){
    BSEARCH_TYPE list[] = {1,2,3,4,5,6,7,8,9};
    int i;
    for(i = 0; i < 10; i++){
        printf("%d ", bin_search(list, 0, 9, i, &compare));
    }
    putchar('\n');
}


//************************************** binary search **********************************************

// search e in list, with range [lo, hi)
// if e does not exist, then return the greatest index of the element that not greater than e
int bin_search(BSEARCH_TYPE* list, int lo, int hi, BSEARCH_TYPE e, int (*cmp)(const void*, const void*)){
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        int mi = (hi + lo)>>1;
        // if e < list[mi] then search [lo, mi) else [mi+1, hi)
        // if e== list[mi], then search [mi+1, hi) until [mi+1, mi+1) and break to return mi+1-1
        if((cmp(&e, list + mi) < 0)) {
            hi = mi;
        } else {
            lo  = mi + 1;
        }
    }
    return --lo;
}
