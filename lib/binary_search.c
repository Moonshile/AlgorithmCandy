#include <stdio.h>
#include <stdlib.h>

//************************************** binary search **********************************************

typedef int LIST_TYPE;
int bin_search(LIST_TYPE*, int, int, LIST_TYPE, int (*)(const void*, const void *));

//************************************** binary search **********************************************

// search e in list, with range [lo, hi)
// if e does not exist, then return the greatest index of the element that not greater than e
int bin_search(LIST_TYPE *list, int lo, int hi, LIST_TYPE e, int (*cmp)(const void*, const void *)){
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        int mi = (hi + lo)>>1;
        // if e < list[mi] then search [lo, mi) else [mi+1, hi)
        // if e== list[mi], then search [mi+1, hi) until [mi+1, mi+1) and break to return mi+1-1
        if(((*cmp)((const void *)e, (const void *)list[mi]) < 0)) {
            hi = mi;
        } else {
            lo  = mi + 1;
        }
    }
    return --lo;
}

int compare(const void *a, const void *b){
    return (int)((long)a - (long)b);
}

int main(){
    LIST_TYPE list[] = {1,2,3,4,5,6,7,8,9};
    int i;
    for(i = 0; i < 10; i++){
        printf("%d ", bin_search(list, 0, 9, i, &compare));
    }
    putchar('\n');
}
