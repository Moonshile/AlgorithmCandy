#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);

#define COORDINATE_RANGE (32768)
#define MAX_W_SUM (2LL<<60)

int main(){
    int n, i, x, w, w_list[COORDINATE_RANGE], x_tmp, min_x;
    static long long wleft[COORDINATE_RANGE], wright[COORDINATE_RANGE], w_sum_tmp, min;
    reset_io();
    memset(w_list, 0, sizeof(int)*COORDINATE_RANGE);
    next_int(&n);
    // input
    for(i = 0; i < n; i++) {
        next_int(&x);
        next_int(&w);
        w_list[x] += w;
    }
    // compute sum of wx in the left side of a point
    wleft[COORDINATE_RANGE - 1] = MAX_W_SUM; // init wleft[COORDINATE_RANGE - 1] so that line 36 (init of min) won't be unpredictable
    for(i = 1, wleft[0] = 0LL, w_sum_tmp = w_list[0], x_tmp = 0; i < COORDINATE_RANGE; i++) {
        if(w_list[i]) {
            // f(n) = f(n - 1) + left_w_sum*delta_n_x
            wleft[i] = wleft[x_tmp] + w_sum_tmp*(i - x_tmp);
            x_tmp = i;
            w_sum_tmp += w_list[i];
        }
    }
    // compute sum of wx in the right side of a point and record the minimum wx value
    x = COORDINATE_RANGE - 1;
    min_x = x;
    min = wleft[x];
    for(i = x - 1, wright[x] = 0LL, w_sum_tmp = w_list[x], x_tmp = x; i >= 0; i--) {
        if(w_list[i]) {
            wright[i] = wright[x_tmp] + w_sum_tmp*(x_tmp - i);
            x_tmp = i;
            w_sum_tmp += w_list[i];
            // determine the minimum wx
            // choose the first minimum point, so don't use < but <=
            if(wleft[i] + wright[i] <= min) {
                min = wleft[i] + wright[i];
                min_x = i;
            }
        }
    }
    printf("%d\n%lld\n", min_x, min);
    return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (100<<10<<10)
#define OUT_BUF_SIZE (10<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
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
