#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_from_stdin();
int next_int(int*);

#define MAX_X (32768)

typedef struct __hospital__ {
    long long sl; // sum of w*x at the left side of hospital
    long long sr; // sum of w*x at the right side of hospital
    long w_sum_l; // sum of w at the left side of hospital, exclude hospital
    long w_sum_r; // sum of w at the right side of hospital, exclude hospital
    int hx; // location of hospital
} Hospital;

void add(Hospital* cur, int* w_list, int n, int x, int w) {
    w_list[x] += w;
    if(x < cur->hx) {
        cur->sl += (long long)w*(cur->hx - x);
        cur->w_sum_l += w;
    } else if(cur->hx < x) {
        cur->sr += (long long)w*(x - cur->hx);
        cur->w_sum_r += w;
    }
}

void moveToLeft(Hospital* cur, Hospital* left, int* w_list, int n) {
    int i = cur->hx - 1;
    while(i >= 0 && !w_list[i]) {i--;}
    if(i < 0) {
        left->sl = cur->sl;
        left->sr = cur->sr;
        left->hx = cur->hx;
        return;
    }
    left->hx = i;
    left->sl = cur->sl - cur->w_sum_l*(cur->hx - i);
    left->sr = cur->sr + (cur->w_sum_r + w_list[cur->hx])*(cur->hx - i);
    left->w_sum_l = cur->w_sum_l - w_list[i];
    left->w_sum_r = cur->w_sum_r + w_list[cur->hx];
}

void moveToRight(Hospital* cur, Hospital* right, int* w_list, int n) {
    int i = cur->hx + 1;
    while(i < MAX_X && !w_list[i]) {i++;}
    if(i >= MAX_X) {
        right->sl = cur->sl;
        right->sr = cur->sr;
        right->hx = cur->hx;
        return;
    }
    right->hx = i;
    right->sl = cur->sl + (cur->w_sum_l + w_list[cur->hx])*(i - cur->hx);
    right->sr = cur->sr - cur->w_sum_r*(i - cur->hx);
    right->w_sum_l = cur->w_sum_l + w_list[cur->hx];
    right->w_sum_r = cur->w_sum_r - w_list[i];
}

int main() {
    int x, w, n, i, *w_list;
    Hospital h, t;
    h.sl = 0;
    h.sr = 0;
    h.w_sum_l = 0;
    h.w_sum_r = 0;
    read_from_stdin();
    next_int(&n);
    w_list = (int*)malloc(sizeof(int)*MAX_X);
    memset(w_list, 0, sizeof(int)*MAX_X);
    next_int(&x);
    next_int(&w);
    x--;
    w_list[x] += w;
    h.hx = x;
    for(i = 1; i < n; i++) {
        next_int(&x);
        next_int(&w);
        x--;
        add(&h, w_list, n, x, w);
        if(x < h.hx) {
            moveToLeft(&h, &t, w_list, n);
            while(t.sl + t.sr < h.sl + h.sr) {
                h = t;
                moveToLeft(&h, &t, w_list, n);
            }
        } else if(h.hx < x) {
            moveToRight(&h, &t, w_list, n);
            while(t.sl + t.sr < h.sl + h.sr) {
                h = t;
                moveToRight(&h, &t, w_list, n);
            }
        }
    }
    printf("%d\n%lld\n", h.hx + 1, h.sl + h.sr);
    return 0;
}

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

