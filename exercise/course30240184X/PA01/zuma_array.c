#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ******************************************************
void reset_io();

//****************************** program ******************************************************

int eliminate(char* zuma, int n, int i) {
    int j = i, old_i = i, old_j = j, len;
    char c;
    // zuma[-1] == zuma_origin[0] == '\0'
    while(zuma[i] == zuma[j]) {
        c = zuma[i];
        len = i == j ? -1 : 0;
        while(i >= 0 && zuma[i] == c){
            i--;
            len++;
        }
        while(j < n && zuma[j] == c){
            j++;
            len++;
        }
        // this loop cannot eliminate anything
        if(len < 3) {
            break;
        }
        old_i = i;
        old_j = j;
    }
    if(old_j - old_i < 4) {
        return n;
    }
    i = old_i + 1;
    for(j = old_j; j < n; j++) {
        zuma[i++] = zuma[j];
    }
    return n - (old_j - old_i - 1);
}

void insert(char* zuma, int n, int i, char c) {
    int j;
    for(j = n - 1; j >= i; j--) {
        zuma[j + 1] = zuma[j];
    }
    zuma[i] = c;
}

#define MAX_LEN (20001)

int main(){
    char* zuma, *zuma_origin, ch;
    int n, i, index, len = 0;
    reset_io();
    zuma_origin = (char*)malloc(sizeof(char)*MAX_LEN);
    zuma_origin[0] = '\0';
    zuma = zuma_origin + 1;
    scanf("%s", zuma);
    ch = getchar();
    while(!(ch == '\n' || ch == '\r')) {
        if(ch >= 'A' && ch <= 'Z') {
            zuma[len++] = ch;
        }
        ch = getchar();
    }
    zuma[len++] = '\0';
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d", &index);
        ch = getchar();
        while(!(ch >= 'A' && ch <= 'Z')) {
            ch = getchar();
        }
        insert(zuma, len++, index, ch);
        eliminate(zuma, len, index);
        printf("%s\n", zuma[0] == '\0' ? "-" : zuma);
    }
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_SIZE (10<<20)
#define OUT_BUF_SIZE (10<<20)

char inbuf[IN_BUF_SIZE];
char outbuf[OUT_BUF_SIZE];

void reset_io() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}
