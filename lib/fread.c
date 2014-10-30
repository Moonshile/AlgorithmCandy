#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();
int next_str(char*);

int main(){
    int n, code;
    read_from_stdin();
    do {
        code = next_int(&n);
        //code = next_char();
        printf("%d ", n);
    } while(code);
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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

int next_str(char *buf) {
    int i = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        c = fread_buf[fread_buf_pointer++];
    }
    while(c != '\n' && c != '\0') {
        buf[i] = fread_buf[fread_buf_pointer++];
        c = buf[i++];
    }
    return c;
}
