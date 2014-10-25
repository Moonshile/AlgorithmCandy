#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_from_stdin();
int next_int(int*);

#define MAX (500000)
char coach[MAX];

// Θ(n)
int main() {
    int n, i, e, *team, *t, abc[3] = {0, 0, 0};
    read_from_stdin();
    memset(coach, 0, MAX);
    next_int(&n);
    team = (int*)malloc(sizeof(int)*n*3);
    for(i = 0; i < n*3; i++) {
        next_int(team + i);
    }
    // simulate the choose, update coach[x] only when coach[x] hasn't been set
    while(abc[0] + abc[1] + abc[2] < n*3) {
        for(i = 0; i < 3; i++) {
            t = team + i*n;
            while(abc[i] < n && coach[t[abc[i]] - 1]) {abc[i]++;}
            if(abc[i] < n) coach[t[abc[i]] - 1] = 'A' + i;
        }
    }
    next_int(&e);
    printf("%c\n", coach[e - 1]);
    return 0;
}

//----------------------------- my libs ----------------------------------------


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
