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
// x and y are arrays to store big integer, and the higher digits are stored RIGHT side
#define MAX_SIZE (3100)
// radix is 1000000000 i.e. 10^9, and 2^32 is about 4 billion
#define RADIX (1000000000)
typedef struct __bigint__ {
    int value[MAX_SIZE];
    int digits;
    int sign;
} Bigint;
// return digits count of result
int convert_to_bigint(char* str, int len, int sign, Bigint* num);
// init as integer
void init_bigint(Bigint* x, int v);
// shift: after multiplication, shift the result to higher digits
void scalar_mult(Bigint* x, Bigint* res, int scalar, int shift);
// add x, y: x = x + y
void add(Bigint* x, Bigint* y);
// minus x, y: x = x - y
void minus(Bigint* x, Bigint* y);
// mult x, y, z, t: z = x*y
void multiple(Bigint* x, Bigint* y, Bigint* res, Bigint* tmp);
// x, digits, sign
void print_bigint(Bigint* num);

Bigint* _bs[3], *_us[3], *_intermediate, *_tmp;

void init_series() {
    int bs[] = {2, 2, 4}, us[] = {0, 0, 0}, i;
    for(i = 0; i < 3; i++) {
        _bs[i] = (Bigint*)malloc(sizeof(Bigint));
        init_bigint(_bs[i], bs[i]);
    }
    for(i = 0; i < 3; i++) {
        _us[i] = (Bigint*)malloc(sizeof(Bigint));
        init_bigint(_us[i], us[i]);
    }
    _intermediate = (Bigint*)malloc(sizeof(Bigint));
    init_bigint(_intermediate, 0);
}

void next_ugly() {
    add(_intermediate, _us[2]);
    add(_intermediate, _us[2]);
    add(_intermediate, _bs[0]);
    _tmp = _us[0];
    _us[0] = _us[1];
    _us[1] = _us[2];
    _us[2] = _intermediate;
    _intermediate = _tmp;
    init_bigint(_intermediate, 0);
}

void next_beautiful() {
    add(_intermediate, _bs[1]);
    add(_intermediate, _bs[1]);
    add(_intermediate, _bs[0]);
    _tmp = _bs[0];
    _bs[0] = _bs[1];
    _bs[1] = _bs[2];
    _bs[2] = _intermediate;
    _intermediate = _tmp;
    init_bigint(_intermediate, 0);
}

Bigint* ugly(int n) {
    int i;
    init_series();
    if(n <= 2) {
        return _intermediate;
    }
    for(i = 2; i < n; i++) {
        next_ugly();
        next_beautiful();
    }
    return _us[2];
}

int main(){
    char* buf = reset_io(), *num;
    int n, i;
    Bigint* x;
    next_int(&n);
    x = ugly(n);
    print_bigint(x);
    free(buf);
    return 0;
}

//***************************** bigint *****************************************

int convert_to_bigint(char* str, int len, int sign, Bigint* num) {
    int i, j = 0, n = 0, radix = 1;
    for(i = len - 1; i >= 0; i--) {
        n += (str[i] - '0')*radix;
        radix *= 10;
        if(radix == RADIX) {
            (num->value)[j++] = n;
            n = 0;
            radix = 1;
        }
    }
    (num->value)[j] = n;
    num->digits =  n == 0 ? j : j + 1;
    num->sign = sign;
    return num->digits;
}

void init_bigint(Bigint* x, int v) {
    memset(x->value, 0, sizeof(int)*MAX_SIZE);
    (x->value)[0] = v;
    x->digits = 1;
    x->sign = v >= 0 ? POSITIVE : NEGATIVE;
}

// shift: after multiplication, shift the result to higher digits
void scalar_mult(Bigint* x, Bigint* res, int scalar, int shift) {
    long i;
    long carry = 0, a, s = scalar;
    res->digits = x->digits;
    for(i = 0; i < x->digits; i++) {
        a = s*(long)((x->value)[i]) + carry;
        (res->value)[i] = (int)(a%RADIX);
        carry = a/RADIX;
    }
    if(carry) {
        (res->value)[i] = (int)carry;
        (res->digits)++;
    }
    // shift
    for(i = res->digits - 1; i >= 0; i--) {
        (res->value)[i + shift] = (res->value)[i];
    }
    for(i = shift - 1; i >= 0; i--) {
        (res->value)[i] = 0;
    }
    res->digits += shift;
}

void add(Bigint* x, Bigint* y) {
    int i, carry = 0, digits = x->digits > y->digits ? x->digits : y->digits;
    for(i = 0; i < digits; i++) {
        // DO NOT forget the carry!!!!!!!!!!!
        (x->value)[i] += (y->value)[i] + carry;
        if((x->value)[i] >= RADIX) {
            (x->value)[i] -= RADIX;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    x->digits = digits;
    if(carry) {
        (x->value)[i] = carry;
        x->digits = digits + 1;
    }
}

void minus(Bigint* x, Bigint* y) {
    int i, carry = 0, digits = x->digits > y->digits ? x->digits : y->digits;
    for(i = 0; i < digits; i++) {
        // DO NOT forget the carry!!!!!!!!!!!
        (x->value)[i] += carry;
        if((x->value)[i] < (y->value)[i]) {
            carry = -1;
            (x->value)[i] += RADIX;
        }
        (x->value)[i] -= (y->value)[i];
    }
    if(carry < 0) {
        x->sign = NEGATIVE;
    }
    x->digits = 1;
    i = 1;
    while((x->value)[i]) {
        (x->digits) ++;
    }
}

void multiple(Bigint* x, Bigint* y, Bigint* res, Bigint* tmp) {
    int i;
    res->digits = 0;
    for(i = 0; i < y->digits; i++) {
        // compute: tmp = x*y[i]
        scalar_mult(x, tmp, (y->value)[i], i);
        // compute: res += tmp
        add(res, tmp);
        // reset tmp
        memset(tmp->value, 0, sizeof(int)*(tmp->digits));
    }
    res->sign = x->sign ^ y->sign;
}

void print_bigint(Bigint* num) {
    int i;
    if(num->sign == NEGATIVE && !(num->digits == 1 && (num->value)[0] == 0)) {
        printf("-");
    }
    for(i = num->digits - 1; i >= 0; i--) {
        printf(i == num->digits - 1 ? "%d" : "%09d", (num->value)[i]);
    }
    printf(num->digits == 0 ? "0\n" : "\n");
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (1<<10)
#define OUT_BUF_SIZE (1<<10)

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
