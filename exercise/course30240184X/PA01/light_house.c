#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin()
{
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

int next_int(int *res)
{
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0'))
    {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0')
    {
        return 0;
    }
    while(c != ' ' && c != '\n' && c != '\0')
    {
        if(c >= '0' && c <= '9')
        {
            *res = (*res)*10 + c - '0';
        }
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

typedef int LIST_TYPE;

#define CUTOFF (3)

// swap the location of a and b
void swap(LIST_TYPE* list_x, LIST_TYPE* list_y, int a, int b) {
    LIST_TYPE tmp = list_x[a];
    list_x[a] = list_x[b];
    list_x[b] = tmp;
    tmp = list_y[a];
    list_y[a] = list_y[b];
    list_y[b] = tmp;
}

// sort a 3-more-element list, which has a range [lo, hi)
void sort3(LIST_TYPE* list_x, LIST_TYPE* list_y, int lo, int hi) {
    int mid = (lo + hi)/2;
    hi--;
    if(list_x[lo] > list_x[mid]) {
        swap(list_x, list_y, lo, mid);
    }
    if(list_x[lo] > list_x[hi]) {
        swap(list_x, list_y, lo, hi);
    }
    if(list_x[mid] > list_x[hi]) {
        swap(list_x, list_y, mid, hi);
    }
}

// select the median of list which has a range [lo, hi)
// the median is the median of elements at the first, middle, and last location in the list
LIST_TYPE median3(LIST_TYPE* list_x, LIST_TYPE* list_y, int lo, int hi) {
    int mid = (lo + hi)/2;
    sort3(list_x, list_y, lo, hi);
    swap(list_x, list_y, mid, hi - 2);
    return list_x[hi - 2];
}

// sort a list with range [lo, hi)
void myQsort(LIST_TYPE* list_x, LIST_TYPE* list_y, int lo, int hi) {
    int i, j;
    LIST_TYPE pivot;
    if(lo + CUTOFF < hi) {
        pivot = median3(list_x, list_y, lo, hi);
        i = lo;
        j = hi - 2;
        for(; ; ) {
            while(list_x[++i] < pivot){}
            while(list_x[--j] > pivot){}
            if(i < j) {
                swap(list_x, list_y, i, j);
            } else {
                break;
            }
        }
        swap(list_x, list_y, i, hi - 2);
        myQsort(list_x, list_y, lo, i);
        myQsort(list_x, list_y, i + 1, hi);
    } else {
        sort3(list_x, list_y, lo, hi);
    }
}

// merge two sub lists that have been sorted
long long merge(LIST_TYPE* list, LIST_TYPE* tmp, int lo, int mi, int hi){
    LIST_TYPE* a = list + lo, *b = tmp + lo, *c = list + mi;
    int len_b = mi - lo, len_c = hi - mi, i, j, k;
    long long res = 0LL;
    // copy b to its temporary location
    for(i = 0; i < len_b; b[i] = a[i++]);
    // the test should be j < len_b && k < len_c, but in fact, 
    // k < len_c is always tested before copy c, so this condition could be omitted
    for(i = 0, j = 0, k = 0; j < len_b; ) {
        // the following two if clause could be exchanged,
        // but will produce extra iterations in this loop
        
        // c hasn't been copied, and c[k] is lower than b[j]
        if(k < len_c && c[k] < b[j]) {
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || b[j] <= c[k]) {
            a[i++] = b[j++];
            res += len_c - k;
        }
    }
    return res;
}

// act merge sort
long long msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int lo, int hi){
    if(lo + 1 < hi)
    {
        int mid = (lo + hi)>>1;
        long long a = msort_do(list, tmp, lo, mid);
        long long b = msort_do(list, tmp, mid, hi);
        long long x = merge(list, tmp, lo, mid, hi);
        return a + b + x;
    }
    return 0LL;
}

// merge sort driver, sort range [lo, hi) of list
long long msort(LIST_TYPE *list, int lo, int hi){
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(hi - lo));
    long long res = msort_do(list, tmp, lo, hi);
    free(tmp);
    return res;
}

int main()
{
    int i, n, x, y, j;
    LIST_TYPE *lights_x, *lights_y;
    long long res = 0;
    read_from_stdin();
    next_int(&n);
    lights_x = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    lights_y = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++)
    {
        next_int(&x);
        next_int(&y);
        lights_x[i] = x;
        lights_y[i] = y;
    }
    myQsort(lights_x, lights_y, 0, n);
    free(lights_x);
    res = msort(lights_y, 0, n);
    free(lights_y);
    printf("%lld", res);
    return 0;
}

