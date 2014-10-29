#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN (100<<10<<10)

char *fread_buf;
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(long *res) {
    char c = fread_buf[fread_buf_pointer++];
    int is_pos = 1;
    while(!(c >= '0' && c <= '9' || c == '\0' || c == '-')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    if(c == '-') {
        is_pos = 0;
        c = fread_buf[fread_buf_pointer++];
    }
    *res = 0;
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    if(!is_pos) {
        *res = -*res;
    }
    return c;
}

typedef long LIST_TYPE;

#define LOW32 (0xffffffffL)
#define HIGH32 (0xffffffff00000000L)
#define GET_X(YX) (YX&LOW32)
// YX1 > YX2 iff Y1 > Y2
#define GET_Y(YX) (YX)

#define MAX_X (100000000)

//***************************** hash map for sort x *******************************************

// map size must be prime
#define MAP_SIZE (11185272)
#define EMPTY (0L)

long _map[MAP_SIZE];

long *init_map() {
    memset(_map, EMPTY, sizeof(long)*MAP_SIZE);
    return _map;
}

#define HASH_FUNC(X) (X%MAP_SIZE)

int find(int x) {
    int p = HASH_FUNC(x), collision = 0;
    while(_map[p] != EMPTY && (int)(_map[p]) != x) {
        p += ((++collision)<<1) - 1;
        if(p > MAP_SIZE) {
            p -= MAP_SIZE;
        }
    }
    return p;
}

void insert(long yx) {
    _map[find((int)yx)] = yx;
}

void put_to_array(long* array) {
    int i, j, p;
    for(i = 1, j = 0; i <= MAX_X; i++) {
        // if _map[find(i)] is EMPTY, i as x must also do not exist
        // else i as x is at _map[find(i)]
        p = find(i);
        if(_map[p]) {
            array[j++] = _map[p];
        }
    }
}

//********************************** merge sort ***********************************************

// merge two sub lists that have been sorted
long long merge(LIST_TYPE* list, LIST_TYPE* tmp, int lo, int mi, int hi) {
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
        if(k < len_c && GET_Y(c[k]) < GET_Y(b[j])) {
            a[i++] = c[k++];
        }
        // c has been copied, OR b[j] is not greater than c[k]
        // (1) if c has been copied, then you should copy b only
        // (2) else if b[j] < c[k], surely you should copy b,
        //     and if b[j] == c[k], you should copy b first to ensure stability.
        if(len_c <= k || GET_Y(b[j]) <= GET_Y(c[k])) {
            a[i++] = b[j++];
            res += len_c - k;
        }
    }
    return res;
}

// act merge sort
long long msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int lo, int hi) {
    if(lo + 1 < hi) {
        int mid = (lo + hi)>>1;
        long long a = msort_do(list, tmp, lo, mid);
        long long b = msort_do(list, tmp, mid, hi);
        long long x = merge(list, tmp, lo, mid, hi);
        return a + b + x;
    }
    return 0LL;
}

// merge sort driver, sort range [lo, hi) of list
long long msort(LIST_TYPE *list, int lo, int hi) {
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(hi - lo));
    long long res = msort_do(list, tmp, lo, hi);
    free(tmp);
    return res;
}

int main() {
    int i, n, j;
    long x, y;
    LIST_TYPE *lights;
    long long res = 0;
    fread_buf = (char*)malloc(sizeof(char)*MAX_BUF_LEN);
    read_from_stdin();
    next_int(&n);
    init_map();
    for(i = 0; i < n; i++) {
        next_int(&x);
        next_int(&y);
        insert((y<<32) | x);
    }
    free(fread_buf);
    lights = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    put_to_array(lights);
    //res = msort(lights, 0, n);
    free(lights);
    printf("%lld", res);
    return 0;
}

