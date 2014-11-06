#include<stdlib.h>
#include<stdio.h>

//*********************************** merge sort *****************************************************

typedef int LIST_TYPE;
void merge(LIST_TYPE*, LIST_TYPE*, int, int, int, int (*)(const void*, const void*));
void msort_do(LIST_TYPE*, LIST_TYPE*, int, int, int (*)(const void*, const void*));
void msort(LIST_TYPE*, int, int, int (*)(const void*, const void*));

//*********************************** merge sort *****************************************************

// merge two sub lists that have been sorted
void merge(LIST_TYPE* list, LIST_TYPE* tmp, int lo, int mi, int hi, int (*cmp)(const void*, const void*)){
    LIST_TYPE* a = list + lo, *b = tmp + lo, *c = list + mi;
    int len_b = mi - lo, len_c = hi - mi, i, j, k;
    // copy b to its temporary location
    for(i = 0; i < len_b; b[i] = a[i++]);
    // the test should be j < len_b && k < len_c, but in fact, 
    // k < len_c is always tested before copy c, so this condition could be omitted
    for(i = 0, j = 0, k = 0; j < len_b; ) {
        // the following two if clause could be exchanged,
        // but will produce extra iterations in this loop
        
        // c hasn't been copied, and c[k] is lower than b[j]
        if(k < len_c && (*cmp)((const void*)(c + k), (const void*)(b + j)) < 0) {
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || (*cmp)((const void*)(b + j), (const void*)(c + k)) <= 0) {
            a[i++] = b[j++];
        }
    }
}

// act merge sort
void msort_do(LIST_TYPE* list, LIST_TYPE* tmp, int lo, int hi, int (*cmp)(const void*, const void*)){
    if(lo + 1 < hi)
    {
        int mid = (lo + hi)>>1;
        msort_do(list, tmp, lo, mid, cmp);
        msort_do(list, tmp, mid, hi, cmp);
        merge(list, tmp, lo, mid, hi, cmp);
    }
}

// merge sort driver, sort range [lo, hi) of list
void msort(LIST_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)){
    LIST_TYPE* tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(hi - lo));
    msort_do(list, tmp, lo, hi, cmp);
    free(tmp);
}

//************************************************* test ****************************************

int compare(const void* x, const void* y){
    return (int)(*(LIST_TYPE*)x - *(LIST_TYPE*)y);
}

int main(){
    LIST_TYPE list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1},
        {1,2,321,564,6,2135,54,321,321}
    };
    int i, j;
    for(i = 0; i < 4; i++){
        msort(list[i], 0, 9, &compare);
        for(j = 0; j < 9; j++){
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
