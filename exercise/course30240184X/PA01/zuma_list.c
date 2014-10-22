#include <stdio.h>
#include <stdlib.h>

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

#define MAX_LEN (20001)

int main()
{
    Chain chain;
    chain.ball = 0;
    Ball *p;
    char c, outs[MAX_LEN];
    int i = 0, n, j, oi;
    while((c = getchar()) != '\n')
    {
        insert(&chain, i++, newBall(c));
    }
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d %c", &j, &c);
        Ball *b = newBall(c);
        insert(&chain, j, b);
        deleteAllSame(&chain, b);
        p = chain.ball;
        oi = 0;
        do
        {
            outs[oi++] = p ? p->color : '-';
            p = p ? p->next : p;
        }while(p);
        outs[oi++] = '\n';
        outs[oi++] = 0;
        printf("%s", outs);
    }
    return 0;
}
