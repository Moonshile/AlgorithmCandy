#include <stdio.h>
#include <stdlib.h>

void reset_buf();



#define IN_BUF_SIZE (100<<20)
#define OUT_BUF_SIZE (10<<20)
char inbuf[IN_BUF_SIZE] = {0};
char outbuf[OUT_BUF_SIZE];

void reset_buf() {
    setvbuf(stdin, inbuf, _IOFBF, IN_BUF_SIZE);
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
}