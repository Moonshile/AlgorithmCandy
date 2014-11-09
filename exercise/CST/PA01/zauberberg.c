#include <stdio.h>
#include <stdlib.h>

typedef struct __creature__ {
    int height;
    int positive;
    int negative;
} Creature;

typedef Creature LIST_TYPE;
typedef double SEARCH_TYPE;

//****************************** fast io ******************************************************
void reset_io();

//*************************************** qsort **************************************************
void swap(LIST_TYPE*, int, int);
void sort3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
LIST_TYPE median3(LIST_TYPE*, int, int, int (*)(const void *, const void *));
void myQsort(LIST_TYPE*, int, int, int (*)(const void *, const void *));

//************************************** binary search **********************************************

// search e in list, with range [lo, hi)
// if e does not exist, then return the greatest index of the element that not greater than e
int bin_search(SEARCH_TYPE*, int, int, SEARCH_TYPE, double (*)(const void*, const void *));
// if e does not exist, then return the lowest index of the element that greater than e
int bin_search_first(SEARCH_TYPE*, int, int, SEARCH_TYPE, double (*)(const void*, const void *));

//*************************************** program ***************************************************

int compare_height(const void *x, const void *y) {
    return ((Creature*)y)->height - ((Creature*)x)->height;
}

double compare_hit(const void *x, const void *y) {
    return (*(SEARCH_TYPE*)x) - (*(SEARCH_TYPE*)y);
}

double compare_false(const void *x, const void *y) {
    return (*(SEARCH_TYPE*)x) - (*(SEARCH_TYPE*)y);
}

int main(){
    char ch;
    int n, h, m, i, j, hh, hf;
    double *phits, *pfalses, phit, pfalse;
    Creature* cs;
    reset_io();
    scanf("%d %d", &n, &h);
    cs = (Creature*)malloc(sizeof(Creature)*n);
    // input
    for(i = 0; i < n; i++) {
        scanf("%d", &(cs[i].height));
        ch = getchar();
        while(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
            ch = getchar();
        }
        if(ch == '+') {
            cs[i].positive ++;
        } else {
            cs[i].negative ++;
        }
    }
    // sort by height desc and unify
    myQsort(cs, 0, n, &compare_height);
    for(i = 0, j = 1; j < n; j++) {
        if(cs[i].height == cs[j].height) {
            cs[i].positive += cs[j].positive;
            cs[i].negative += cs[j].negative;
        } else {
            i++;
            cs[i].height = cs[j].height;
            cs[i].positive = cs[j].positive + cs[i - 1].positive;
            cs[i].negative = cs[j].negative + cs[i - 1].negative;
        }
    }
    // now n is count of height
    n = i + 1;
    // compute phit and pfalse
    phits = (double*)malloc(sizeof(double)*n);
    pfalses = (double*)malloc(sizeof(double)*n);
    // phits: desc by height
    for(i = 0; i < n; i++) {
        phits[i] = ((double)cs[i].positive)/cs[n - 1].positive;
    }
    // pfalses: desc by height
    for(i = 0; i < n; i++) {
        pfalses[i] = ((double)cs[i].negative)/cs[n - 1].negative;
    }
    // search
    scanf("%d", &m);
    for(i = 0; i < m; i++) {
        scanf("%lf %lf", &phit, &pfalse);
        // hits is sorted desc, so need minus by n-1
        hh = bin_search_first(phits, 0, n, phit, &compare_hit);
        hf = bin_search(pfalses, 0, n, pfalse, &compare_false);
        //convert to height
        hh = cs[hh].height;
        // remember: hh is not lower than 0 forever
        if(phit <= 0.0f) {
            hh = h;
        }
        if(hf < n - 1) {
            hf = cs[hf + 1].height + 1;
        } else {
            hf = 0;
        }
        if(hf > hh) {
            printf("-1\n");
        } else {
            printf("%d %d\n", hf, hh);
        }
    }
    free(cs);
    free(phits);
    free(pfalses);
    return 0;
}

//****************************** fast io ***********************************************************
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
void swap(LIST_TYPE *list, int a, int b) {
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int mid = (lo + hi)>>1;
    hi--;
    if((*cmp)((const void *)(list + lo), (const void *)(list + mid)) > 0) {
        swap(list, lo, mid);
    }
    if((*cmp)((const void *)(list + lo), (const void *)(list + hi)) > 0) {
        swap(list, lo, hi);
    }
    if((*cmp)((const void *)(list + mid), (const void *)(list + hi)) > 0) {
        swap(list, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int mid = (lo + hi)>>1;
    sort3(list, lo, hi, cmp);
    swap(list, mid, hi - 2);
    return list[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE *list, int lo, int hi, int (*cmp)(const void *, const void *)) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list, lo, hi, cmp);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while((*cmp)((const void *)(list + (++i)), (const void *)&pivot) < 0){}
            while((*cmp)((const void *)(list + (--j)), (const void *)&pivot) > 0){}
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
int bin_search(SEARCH_TYPE *list, int lo, int hi, SEARCH_TYPE e, double (*cmp)(const void*, const void *)){
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        int mi = (hi + lo)>>1;
        // if e < list[mi] then search [lo, mi) else [mi+1, hi)
        // if e== list[mi], then search [mi+1, hi) until [mi+1, mi+1) and break to return mi+1-1
        if(((*cmp)((const void *)&e, (const void *)(list + mi)) < 0.0f)) {
            hi = mi;
        } else {
            lo  = mi + 1;
        }
    }
    return --lo;
}

int bin_search_first(SEARCH_TYPE *list, int lo, int hi, SEARCH_TYPE e, double (*cmp)(const void*, const void *)){
    while(lo < hi){
        int mi = (hi + lo)>>1;
        if(((*cmp)((const void *)&e, (const void *)(list + mi)) > 0.0f)) {
            lo  = mi + 1;
        } else {
            hi = mi;
        }
    }
    return lo;
}
