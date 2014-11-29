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
void merge(MSORT_TYPE*, MSORT_TYPE*, int, int, int, int (*)(const void*, const void*), int);
int msort_do(MSORT_TYPE*, MSORT_TYPE*, int, int, int (*)(const void*, const void*));
void msort(MSORT_TYPE*, int, int, int (*)(const void*, const void*));
//*************************************** qsort **************************************************
void swap(QSORT_TYPE*, int, int);
void sort3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
QSORT_TYPE median3(QSORT_TYPE*, int, int, int (*)(const void*, const void*));
void myQsort(QSORT_TYPE*, int, int, int (*)(const void*, const void*));

//****************************** program ******************************************************

#define LIGHT_INDEX (100000000)
#define MAX_SIZE (300000)

struct __light_house__ {
    int x;
    int y;
    int index; // MAX_INDEX for light points
    int count; // count corresponding points for the query points
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

int compareXYDesc(const void* x, const void* y) {
    if(((LightHouse*)y)->x - ((LightHouse*)x)->x != 0) {
        return ((LightHouse*)y)->x - ((LightHouse*)x)->x;
    }
    return ((LightHouse*)y)->y - ((LightHouse*)x)->y;
}

int compareYDesc(const void* x, const void* y) {
    return ((LightHouse*)y)->y - ((LightHouse*)x)->y;
}

int compareIndex(const void* x, const void* y) {
    return ((LightHouse*)x)->index - ((LightHouse*)y)->index;
}

int main(){
    int n, k, i;
    LightHouse* lhAsc, *lhDesc;
    reset_io();
    // sorted ascendantly for query point at right top side
    lhAsc = (LightHouse*)malloc(sizeof(LightHouse)*MAX_SIZE);
    // sorted in descendant for query point at left bottom side
    lhDesc = (LightHouse*)malloc(sizeof(LightHouse)*MAX_SIZE);
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d %d", &(lhAsc[i].x), &(lhAsc[i].y));
        lhAsc[i].count = 0;
        lhAsc[i].index = LIGHT_INDEX;
    }
    memcpy(lhDesc, lhAsc, sizeof(LightHouse)*n);
    scanf("%d", &k);
    // if n is 0, simply put 0 out
    if(n == 0) {
        for(i = 0; i < k; i++) {
            printf("0\n");
        }
        return 0;
    }
    // put right top query points to lhAsc, and the left bottom query point to lhDesc
    n += k;
    for(; i < n; i++) {
        scanf("%d %d %d %d", &(lhDesc[i].x), &(lhDesc[i].y), &(lhAsc[i].x), &(lhAsc[i].y));
        lhAsc[i].count = 0;
        lhAsc[i].index = i;
        lhDesc[i].count = 0;
        lhDesc[i].index = i;
    }
    // sort by x and y
    myQsort(lhAsc, 0, n, compareXY);
    myQsort(lhDesc, 0, n, compareXYDesc);
    // sort by y and count
    // DIVIDE & CONQUER strategy
    msort(lhAsc, 0, n, compareY);
    msort(lhDesc, 0, n, compareYDesc);
    // sort by x and y
    myQsort(lhAsc, 0, n, compareIndex);
    myQsort(lhDesc, 0, n, compareIndex);
    for(i = 0; i < k; i++) {
        printf("%d\n", lhAsc[i].count + lhDesc[i].count);
    }
    free(lhAsc);
    free(lhDesc);
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
void merge(MSORT_TYPE* list, MSORT_TYPE* tmp, int lo, int mi, int hi, int (*cmp)(const void*, const void*), int qc){
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
            if(c[k].index != LIGHT_INDEX) {
                qc--;
            }
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || cmp(b + j, c + k) <= 0) {
            if(len_c > k && b[j].index != LIGHT_INDEX) {
                b[j].count += len_c - k - qc;
            } else if(len_c > k && b[j].index == LIGHT_INDEX && c[k].index != LIGHT_INDEX && compareXY(b + j, c + k) == 0) {
                // if bj is a light and ck is a query point at bj, 
                // then inc count of ck as well as all same query points following ck
                for(w = k; w < len_c && compareXY(b + j, c + w) == 0; w++) {
                    if(c[w].index != LIGHT_INDEX) {
                        c[w].count++;
                    }
                }
            }
            a[i++] = b[j++];
        }
    }
}

// act merge sort
int msort_do(MSORT_TYPE* list, MSORT_TYPE* tmp, int lo, int hi, int (*cmp)(const void*, const void*)){
    if(lo + 1 < hi)
    {
        int mid = (lo + hi)>>1;
        int q1 = msort_do(list, tmp, lo, mid, cmp);
        int q2 = msort_do(list, tmp, mid, hi, cmp);
        merge(list, tmp, lo, mid, hi, cmp, q2);
        return q1 + q2;
    }
    return list[lo].index == LIGHT_INDEX ? 0 : 1;
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

