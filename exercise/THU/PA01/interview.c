#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();

typedef struct __interviewee__ {
    int id;
    struct __interviewee__* pre;
    struct __interviewee__* next;
} Interviewee;

// insert interviewee inter into the desk at index of m, from start as index 0
// return the inserted interviewee
Interviewee* insert(Interviewee* start, Interviewee* inter, int m) {
    if(start) {
        while(--m) {
            start = start->next;
        }
        inter->next = start->next;
        inter->pre = start;
        start->next->pre = inter;
        start->next = inter;
    }
    return inter;
}

int main() {
    int n, m, i;
    Interviewee* desk = 0, *inters;
    char *buf = reset_io();
    next_int(&n);
    next_int(&m);
    inters = (Interviewee*)malloc(sizeof(Interviewee)*n);
    desk = inters;
    if(n > 0) {
        next_int(&(desk->id));
        desk->pre = desk;
        desk->next = desk;
    }
    for(i = 1; i < n; i++) {
        next_int(&(inters[i].id));
        desk = insert(desk, inters + i, m);
    }
    buf[0] = '\0';
    for(i = 0; i < n - 1; i++) {
        sprintf(buf + strlen(buf), "%d \0", desk->id);
        desk = desk->pre;
    }
    if(n > 0) {
        sprintf(buf + strlen(buf), "%d\n\0", desk->id);
    }
    printf("%s", buf);
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
