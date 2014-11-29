#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __light_house__ LightHouse;
typedef LightHouse MSORT_TYPE;
typedef LightHouse QSORT_TYPE;
typedef LightHouse BSEARCH_TYPE;

//****************************** fast io ******************************************************
void reset_io();
//*********************************** merge sort *****************************************************
void merge(MSORT_TYPE*, MSORT_TYPE*, int, int, int, int (*)(const void*, const void*));
void msort_do(MSORT_TYPE*, MSORT_TYPE*, int, int, int (*)(const void*, const void*));
void msort(MSORT_TYPE*, int, int, int (*)(const void*, const void*));
//*************************************** qsort **************************************************
void swap(QSORT_TYPE*, int, int);
void sort3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
QSORT_TYPE median3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
//************************************** binary search **********************************************
int bin_search(BSEARCH_TYPE*, int, int, BSEARCH_TYPE, int (*)(const void*, const void*));

//****************************** program ******************************************************

struct __light_house__ {
    int x;
    int y;
    int count; // points same with this
    int notLower; // points not lower than this
    int notGreater; // points not greater than this
};

int compareX(const void* x, const void* y) {
    return ((LightHouse*)x)->x - ((LightHouse*)y)->x;
}

int compareY(const void* x, const void* y) {
    return ((LightHouse*)x)->y - ((LightHouse*)y)->y;
}

int compareXY(const void* x, const void* y) {
    if(((LightHouse*)x)->x - ((LightHouse*)y)->x != 0) {
        return ((LightHouse*)x)->x - ((LightHouse*)y)->x;
    }
    return ((LightHouse*)x)->y - ((LightHouse*)y)->y;
}

int compareYX(const void* x, const void* y) {
    if(((LightHouse*)x)->y - ((LightHouse*)y)->y != 0) {
        return ((LightHouse*)x)->y - ((LightHouse*)y)->y;
    }
    return ((LightHouse*)x)->x - ((LightHouse*)y)->x;
}

int main(){
    int n, k, i, i1, i2, c1, c2;
    LightHouse* lhx, *lhy, lh1, lh2;
    reset_io();
    scanf("%d", &n);
    lhx = (LightHouse*)malloc(sizeof(LightHouse)*n);
    lhy = (LightHouse*)malloc(sizeof(LightHouse)*n);
    for(i = 0; i < n; i++) {
        scanf("%d %d", &(lhx[i].x), &(lhx[i].y));
        lhx[i].notLower = 1;
        lhx[i].notGreater = 1;
        lhx[i].count = 1;
    }
    // sort by x
    myQsort(lhx, 0, n, compareX);
    // sort by y and compute not Lower/notGreater
    msort(lhx, 0, n, compareY);
    memcpy(lhy, lhx, sizeof(LightHouse)*n);/*
    // sort by x and y
    myQsort(lhx, 0, n, compareXY);
    memcpy(lhy, lhx, sizeof(LightHouse)*n);
    // sort by y and x
    myQsort(lhy, 0, n, compareYX);
    scanf("%d", &k);
    for(i = 0; i < k; i++) {
        scanf("%d %d %d %d", &(lh1.x), &(lh1.y), &(lh2.x), &(lh2.y));
        i1 = bin_search(lhx, 0, n, lh1, compareXY);
        i2 = bin_search(lhy, 0, n, lh2, compareYX);
        if(compareYX(&lh2, lhy + i2) != 0) {
            i2++;
        }
        c1 = i1 == -1 ? 0 : lhx[i1].notGreater;
        c2 = i2 == n ? 0 : lhy[i2].notLower;
        c1 += i1 >=0 && i2 < n && compareXY(lhx + i1, lhy + i2) == 0 ? c2 - lhy[i2].count : c2;
        printf("%d\n", c1);
    }*/
    for(i = 0; i < n; i++) {
        lhy[i].notLower = 0;
        lhy[i].notGreater = 0;
        for(i1 = 0; i1 < n; i1++) {
            if(compareX(lhx + i1, lhy + i) <= 0 && compareY(lhx + i1, lhy + i) <= 0) {
                lhy[i].notGreater++;
            }
        }
        for(i1 = 0; i1 < n; i1++) {
            if(compareX(lhx + i1, lhy + i) >= 0 && compareY(lhx + i1, lhy + i) >= 0) {
                lhy[i].notLower++;
            }
        }
    }
    for(i = 0; i < n; i++) {
        if(lhx[i].notLower != lhx[i].notLower && lhx[i].notGreater != lhy[i].notGreater) {
            printf("x:%d y:%d nl:%d wnl:%d ng:%d wng:%d\n", lhx[i].x, lhx[i].y, lhy[i].notLower, lhx[i].notLower, lhy[i].notGreater, lhx[i].notGreater);
        }
    }
    scanf("%d", &k);
    for(i = 0; i < k; i++) {
        scanf("%d %d %d %d", &(lh1.x), &(lh1.y), &(lh2.x), &(lh2.y));
        c1 = 0;
        for(i1 = 0; i1< n; i1++) {
            if(compareX(lhx + i1, &lh1) <= 0 && compareY(lhx + i1, &lh1) <= 0) {
                c1++;
            }
        }
        if(compareYX(&lh1, &lh2) != 0) {
            for(i1 = 0; i1< n; i1++) {
                if(compareX(lhx + i1, &lh2) >= 0 && compareY(lhx + i1, &lh2) >= 0) {
                    c1++;
                }
            }
        } else {
            for(i1 = 0; i1< n; i1++) {
                if(compareX(lhx + i1, &lh2) > 0 && compareY(lhx + i1, &lh2) > 0) {
                    c1++;
                }
            }
        }
        printf("%d\n", c1);
    }
    free(lhx);
    free(lhy);
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

//*********************************** merge sort *****************************************************

// merge two sub lists that have been sorted
void merge(MSORT_TYPE* list, MSORT_TYPE* tmp, int lo, int mi, int hi, int (*cmp)(const void*, const void*)){
    MSORT_TYPE* a = list + lo, *b = tmp + lo, *c = list + mi;
    int len_b = mi - lo, len_c = hi - mi, i, j, k, w;
    // copy b to its temporary location
    for(i = 0; i < len_b; b[i] = a[i++]);
    // the test should be j < len_b && k < len_c, but in fact, 
    // k < len_c is always tested before copy c, so this condition could be omitted
    for(i = 0, j = 0, k = 0; j < len_b; ) {
        // the following two if clause could be exchanged,
        // but will produce extra iterations in this loop
        
        // c hasn't been copied, and c[k] is lower than b[j]
        if(k < len_c && cmp(c + k, b + j) < 0) {
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || cmp(b + j, c + k) <= 0) {
            if(len_c > k && cmp(b + j, c + k) == 0) {
                b[j].notLower += len_c - k;
                for(w = k; w < len_c; w++) {
                    c[w].notGreater++;
                }
                b[j].count++;
                c[k].count++;
                if(compareX(b + j, c + k) == 0) {
                    b[j].notGreater++;
                    c[k].notLower++;
                }
            } else if(len_c > k) {
                b[j].notLower += len_c - k;
                for(w = k; w < len_c; w++) {
                    c[w].notGreater++;
                }
            }
            a[i++] = b[j++];
        }
    }
}

// act merge sort
void msort_do(MSORT_TYPE* list, MSORT_TYPE* tmp, int lo, int hi, int (*cmp)(const void*, const void*)){
    if(lo + 1 < hi)
    {
        int mid = (lo + hi)>>1;
        msort_do(list, tmp, lo, mid, cmp);
        msort_do(list, tmp, mid, hi, cmp);
        merge(list, tmp, lo, mid, hi, cmp);
    }
}

// merge sort driver, sort range [lo, hi) of list
void msort(MSORT_TYPE* list, int lo, int hi, int (*cmp)(const void*, const void*)){
    MSORT_TYPE* tmp = (MSORT_TYPE*)malloc(sizeof(MSORT_TYPE)*(hi - lo));
    msort_do(list, tmp, lo, hi, cmp);
    free(tmp);
}

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

