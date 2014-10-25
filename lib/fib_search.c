#include <stdio.h>
#include <stdlib.h>

typedef int LIST_TYPE;
int fib(int);
int fib_get();
int fib_pre();
int fib_next();
int fib_search(LIST_TYPE*, int, int, LIST_TYPE, int (*)(const void*, const void *));

int __fib_cur = 0;
int __fib_next = 1;

// get the greatest Fibonacci number that lower than n
int fib(int n){
    while(__fib_next < n){
        fib_next();
    }
    return __fib_cur;
}

// get current Fibonacci number
int fib_get(){
    return __fib_cur;
}

// get previous Fibonacci number
int fib_pre(){
    __fib_cur = __fib_next - __fib_cur;
    __fib_next -= __fib_cur;
    return __fib_cur;
}

// get next Fibonacci number
int fib_next(){
    __fib_next += __fib_cur;
    __fib_cur = __fib_next - __fib_cur;
    return __fib_cur;
}

// search e in list, with range [lo, hi), and if e does not exist, return -1
int fib_search(LIST_TYPE *list, int lo, int hi, LIST_TYPE e, int (*cmp)(const void*, const void *)){
    int mi;
    // locate the Fibonacci numbers to the greatest one that lower than hi - lo
    fib(hi - lo);
    // invariant: list[lo] <= e < list[hi]
    while(lo < hi){
        // In the first execution of this loop, fib_get() return the greatest number that lower than hi-lo, so hi-lo > fib_get()
        // In the latter executions, hi-lo becomes fib_pre() or fib_pre_pre(), thus this loop will has at most 2 times of iterations.
        while((hi - lo) < fib_get()){
            fib_pre();
        }
        mi = lo + fib_get() - 1;
        if((*cmp)((const void *)e, (const void *)list[mi]) < 0) {
            hi = mi;
        } else if ((*cmp)((const void *)list[mi], (const void *)e) < 0) {
            lo = mi + 1;
        } else {
            return mi;
        }
    }
    return -1;
}

int compare(const void *a, const void *b){
    return (int)((long)a - (long)b);
}

int main(){
    LIST_TYPE list[] = {1,2,3,4,5,6,7,8,9};
    LIST_TYPE list2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    int i;
    for(i = 0; i < 10; i++){
        printf("%d ", fib_search(list, 0, 9, i, &compare));
    }
    putchar('\n');
    for(i = 0; i < 14; i++){
        printf("%d ", fib_search(list2, 0, 13, i, &compare));
    }
    putchar('\n');
}
