#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ******************************************************
void reset_io();

//****************************** program ******************************************************

int main(){
    // variable definitions
    reset_io();
    // todo
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
