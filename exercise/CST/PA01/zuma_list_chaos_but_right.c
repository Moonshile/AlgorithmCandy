#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin()
{
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

int next_int(int *res)
{
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0'))
    {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0')
    {
        return 0;
    }
    while(c != ' ' && c != '\n' && c != '\0')
    {
        if(c >= '0' && c <= '9')
        {
            *res = (*res)*10 + c - '0';
        }
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

char next_char()
{
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0' || c == '\n'))
    {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

typedef struct __ball__ {
    char color;
    struct __ball__ *pre;
    struct __ball__ *next;
} Ball;

typedef struct __chain__ {
    Ball *ball;
} Chain;

Ball *newBall(char color)
{
    Ball *ret = (Ball*)malloc(sizeof(Ball));
    ret->color = color;
    ret->pre = 0;
    ret->next = 0;
}

void insert(Chain *chain, int i, Ball *ball)
{
    if(!chain->ball)
    {
        chain->ball = ball;
    }
    else
    {
        Ball *p = chain->ball;
        while(i--)
        {
            if(!(p->next))
            {
                p->next = ball;
                ball->pre = p;
                return;
            }
            p = p->next;
        }
        ball->pre = p->pre;
        ball->next = p;
        if(!(p->pre))
        {
            chain->ball = ball;
        }
        else
        {
            p->pre->next = ball;
        }
        p->pre = ball;
    }
}

void deleteBall(Chain *chain, Ball *p)
{
    if(p->pre)
    {
        p->pre->next = p->next;
    }
    else
    {
        chain->ball = p->next;
    }
    if(p->next)
    {
        p->next->pre = p->pre;
    }
    free(p);
}

void deleteAt(Chain *chain, int i)
{
    Ball *p = chain->ball;
    while(i--)
    {
        p = p->next;
    }
    deleteBall(chain, p);
}

void deleteAllSame(Chain *chain, Ball *ball)
{
    char c;
    if(!ball)
    {
        return;
    }
    c = ball->color;
    if(ball->pre && ball->pre->pre && ball->pre->color == c && ball->pre->pre->color == c ||
        ball->pre && ball->next && ball->pre->color == c &&  ball->next->color == c ||
        ball->next && ball->next->next && ball->next->color == c && ball->next->next->color == c)
    {
        Ball *i = ball->pre, *j = ball->next, *t;
        while(i && i->color == c)
        {
            t = i;
            i = i->pre;
            deleteBall(chain, t);
        }
        while(j && j->color == c)
        {
            t = j;
            j = j->next;
            deleteBall(chain, t);
        }
        i = ball->pre;
        deleteBall(chain, ball);
        deleteAllSame(chain, i);
    }
}

#define MAX_LEN (100<<10<<10)
char outs[MAX_LEN];

int main()
{
    Chain chain;
    chain.ball = 0;
    Ball *p;
    char c;
    int i = 0, n, j, oi = 0;
    read_from_stdin();
    while((c = next_char()) != '\n')
    {
        insert(&chain, i++, newBall(c));
    }
    next_int(&n);
    for(i = 0; i < n; i++)
    {
        next_int(&j);
        c = next_char();
        Ball *b = newBall(c);
        insert(&chain, j, b);
        deleteAllSame(&chain, b);
        p = chain.ball;
        do
        {
            outs[oi++] = p ? p->color : '-';
            p = p ? p->next : p;
        }while(p);
        outs[oi++] = '\n';
        if(oi >= 90<<10<<10)
        {
            outs[oi++] = 0;
            printf("%s", outs);
            oi = 0;
        }
    }
    outs[oi++] = 0;
    printf("%s", outs);
    return 0;
}
