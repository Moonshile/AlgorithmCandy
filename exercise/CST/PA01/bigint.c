#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
// return the length of str, and the arg will point to somewhere of buffer
int next_number(char**, int*);

//***************************** bigint *****************************************
#define POSITIVE (0)
#define NEGATIVE (1)
#define MAX_SIZE (100)
// radix is 1000000000 i.e. 10^9, and 2^32 is about 4 billion
#define RADIX (1000000000)
// return digits count of result
int convert_to_bigint(char*, int, int*);
void multiple(int*, int, int*, int, int*, int*, int*);
void print_bigint(int*, int, int);

int main(){
    char* buf = reset_io(), *num;
    // x and y are arrays to store big integer, and the higher digits are stored RIGHT side
    int n, i, len, x[MAX_SIZE], y[MAX_SIZE], mult[MAX_SIZE], tmp[MAX_SIZE], sign_x, sign_y, digits_x, digits_y, digits_mult;
    next_int(&n);
    memset(x, 0, sizeof(int)*MAX_SIZE);
    memset(y, 0, sizeof(int)*MAX_SIZE);
    memset(mult, 0, sizeof(int)*MAX_SIZE);
    memset(tmp, 0, sizeof(int)*MAX_SIZE);
    for(i = 0; i < n; i++) {
        len = next_number(&num, &sign_x);
        digits_x = convert_to_bigint(num, len, x);
        len = next_number(&num, &sign_y);
        digits_y = convert_to_bigint(num, len, y);
        multiple(x, digits_x, y, digits_y, mult, &digits_mult, tmp);
        print_bigint(mult, digits_mult, sign_x^sign_y);
        memset(x, 0, sizeof(int)*digits_x);
        memset(y, 0, sizeof(int)*digits_y);
        memset(mult, 0, sizeof(int)*digits_mult);
    }
    free(buf);
    return 0;
}

//***************************** bigint *****************************************

int convert_to_bigint(char* str, int len, int* num) {
    int i, j = 0, n = 0, radix = 1;
    for(i = len - 1; i >= 0; i--) {
        n += (str[i] - '0')*radix;
        radix *= 10;
        if(radix == RADIX) {
            num[j++] = n;
            n = 0;
            radix = 1;
        }
    }
    num[j] = n;
    return n == 0 ? j : j + 1;
}

// shift: after multiplication, shift the result to higher digits
void scalar_mult(int* x, int digits_x, int* res, int* digits_res, int scalar, int shift) {
    long i;
    long carry = 0, a, s = scalar;
    *digits_res = digits_x;
    for(i = 0; i < digits_x; i++) {
        a = s*(long)(x[i]) + carry;
        res[i] = (int)(a%RADIX);
        carry = a/RADIX;
    }
    if(carry) {
        res[i] = (int)carry;
        (*digits_res)++;
    }
    // shift
    for(i = *digits_res - 1; i >= 0; i--) {
        res[i + shift] = res[i];
    }
    for(i = shift - 1; i >= 0; i--) {
        res[i] = 0;
    }
    *digits_res += shift;
}

void add(int* x, int* digits_x, int* y, int digits_y) {
    int i, carry = 0, a, digits = *digits_x > digits_y ? *digits_x : digits_y;
    for(i = 0; i < digits; i++) {
        // DO NOT forget the carry!!!!!!!!!!!
        a = x[i] + y[i] + carry;
        x[i] = a%RADIX;
        carry = a/RADIX;
    }
    if(carry) {
        x[i] = carry;
        *digits_x = digits + 1;
    }
    *digits_x = digits;
}

void multiple(int* x, int digits_x, int* y, int digits_y, int* res, int* digits_res, int* tmp) {
    int i, digits_tmp;
    *digits_res = 0;
    for(i = 0; i < digits_y; i++) {
        // compute: tmp = x*y[i]
        scalar_mult(x, digits_x, tmp, &digits_tmp, y[i], i);
        // compute: res += tmp
        add(res, digits_res, tmp, digits_tmp);
        // reset tmp
        memset(tmp, 0, sizeof(int)*digits_tmp);
    }
}

void print_bigint(int* num, int digits, int sign) {
    int i;
    if(sign == NEGATIVE && !(digits == 1 && num[0] == 0)) {
        printf("-");
    }
    for(i = digits - 1; i >= 0; i--) {
        printf(i == digits - 1 ? "%d" : "%09d", num[i]);
    }
    printf(digits == 0 ? "0\n" : "\n");
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (10<<10<<10)
#define OUT_BUF_SIZE (10<<20)

char *fread_buf;
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    fread_buf = (char*)malloc(sizeof(char)*IN_BUF_LEN);
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

// return the length of str, and the arg will point to somewhere of buffer
int next_number(char **buf, int* sign) {
    int i = 0;
    char c = fread_buf[fread_buf_pointer++];
    *sign = POSITIVE;
    while(!(c >= '0' && c <= '9' || c == '+' || c == '-')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '-') {
        *sign = NEGATIVE;
        c = fread_buf[fread_buf_pointer++];
    }
    *buf = fread_buf + fread_buf_pointer - 1;
    while(c >= '0' && c <= '9') {
        c = fread_buf[fread_buf_pointer++];
        i++;
    }
    return i;
}
