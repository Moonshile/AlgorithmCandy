#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();

typedef struct __ball__ {
    char color;
    struct __ball__ *pre;
    struct __ball__ *next;
} Ball;

typedef struct __chain__ {
    Ball* header;
    Ball* trailer;
    int size;
} Chain;

#define MAX_BALL_COUNT (20000)

Ball _balls[MAX_BALL_COUNT];
int _ball_pointer = 0;

Ball *newBall(char color) {
    Ball *ret = _balls + (_ball_pointer++);
    ret->color = color;
    ret->pre = 0;
    ret->next = 0;
    return ret;
}

Chain* newChain() {
    Chain* c = (Chain*)malloc(sizeof(Chain));
    c->header = newBall(0);
    c->trailer = newBall(0);
    c->size = 0;
    c->header->next = c->trailer;
    c->trailer->pre = c->header;
    return c;
}

void insert(Chain *chain, int i, Ball *ball) {
    Ball* b = chain->header;
    while(i--) {
        b = b->next;
    }
    ball->pre = b;
    ball->next = b->next;
    b->next->pre = ball;
    b->next = ball;
    chain->size ++;
}

void deleteBall(Chain *chain, Ball *p) {
    p->pre->next = p->next;
    p->next->pre = p->pre;
    chain->size --;
}

void deleteRange(Chain* chain, Ball* header, Ball* trailer, int count) {
    if(count) {
        header->next = trailer;
        trailer->pre = header;
        chain->size -= count;
    }
}

void deleteAllSame(Chain *chain, Ball *ball)
{
    int count_pre = 0, count_next = 0, total_count = 0;
    Ball* pre = ball, *next = ball->next;
    char color_pre = pre->color, color_next = next->color;
    while(1) {
        Ball* p = pre, *n = next;
        count_pre = 0;
        count_next = 0;
        //search pre
        while(color_pre && pre->color == color_pre) {
            pre = pre->pre;
            count_pre++;
        }
        // search next
        while(color_next && next->color == color_next) {
            next = next->next;
            count_next++;
        }
        // if current search must stop
        // if two side have same color and can be eliminated
        if(color_pre == color_next && count_pre + count_next >= 3 || count_pre >= 3 && count_next >= 3) {
            color_pre = pre->color;
            color_next = next->color;
            total_count += count_pre + count_next;
            continue;
        }
        // if pre can be eliminated
        if(count_pre >= 3) {
            color_pre = pre->color;
            total_count += count_pre;
            // don't search next in next loop
            next = n;
            continue;
        }
        // if next can be eliminated
        if(count_next >= 3) {
            color_next = next->color;
            total_count += count_next;
            // don't search pre in next loop
            pre = p;
            continue;
        }
        // if cannot eliminate
        pre = p;
        next = n;
        break;
    }
    if(total_count) {
        deleteRange(chain, pre, next, total_count);
    }
}

#define MAX_LEN (10<<20)
char outs[MAX_LEN];

int main() {
    Chain* chain = newChain();
    char c;
    Ball *b;
    int i = 0, n, j, oi = 0;
    char* buf = reset_io();
    while((c = next_char()) != '\n') {
        insert(chain, i++, newBall(c));
    }
    next_int(&n);
    for(i = 0; i < n; i++) {
        next_int(&j);
        c = next_char();
        b = newBall(c);
        insert(chain, j, b);
        deleteAllSame(chain, b);
        b = chain->header;
        j = chain->size;
        do {
            b = b->next;
            outs[oi++] = j-- ? b->color : '-';
        }while(j > 0);
        outs[oi++] = '\n';
        if(oi >= 9<<20) {
            outs[oi++] = 0;
            printf("%s", outs);
            oi = 0;
        }
    }
    outs[oi++] = 0;
    printf("%s", outs);
    free(buf);
    return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (10<<20)
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

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0'|| c == '\n')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
