#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ******************************************************
// return the input buffer
char *reset_io();

//******************************* program *****************************************************

#define IS_CHAR(c) (c >= 'A' && c <= 'Z')
#define MAX_CYCLE (12)

typedef unsigned long long HashType;

HashType hashNextStr(char* str, int* p) {
    HashType v = 0;
    while(IS_CHAR(str[*p])) {
        v = (v << 5) + str[*p];
        (*p)++;
    }
    do {
        str[*p] = 0;
        (*p)++;
    } while(!IS_CHAR(str[*p]) && str[*p] != 0);
    return v;
}

int match(const HashType pattern, HashType text, const char* p, const char* t) {
    int i = 0, len = strlen(t), slen = len - 1;
    HashType tmp;
    do {
        if(pattern == text && strncmp(p + (len - i), t, i) == 0 && strncmp(p, t + i, len - i) == 0) {
            return 1;
        }
        tmp = t[i++];
        // I don't know why 1ULL<<64 == 1 but not 0...
        text = (slen > MAX_CYCLE ? text<<5 : (text - (tmp<<(5*slen)))<<5) + tmp;
    } while(i < len);
    return 0;
}

int main(){
    char* buf = reset_io(), *str1, *str2;
    int p = 0;
    HashType v1, v2;
    if(buf[0] == 0) {
        return 0;
    }
    do {
        str1 = buf + p;
        v1 = hashNextStr(buf, &p);
        str2 = buf + p;
        v2 = hashNextStr(buf, &p);
        printf(strlen(str1) == strlen(str2) && match(v1, v2, str1, str2) ? "YES\n" : "NO\n");
    } while(buf[p] != 0);
    return 0;
}

//****************************** fast io *******************************************************
#define IN_BUF_LEN (10<<20)
#define OUT_BUF_SIZE (1<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
    return fread_buf;
}
