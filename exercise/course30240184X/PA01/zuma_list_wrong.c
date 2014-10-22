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

void deleteAllSameOneByOne(Chain *chain, Ball *ball)
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
        deleteAllSameOneByOne(chain, i);
    }
}

int deleteAllSameTogether(Chain *chain, Ball **left, Ball **right)
{
    if((*left)->pre && (*left)->pre->color == (*right)->color ||
        (*right)->next && (*right)->next->color == (*left)->color)
    {
        while((*left) && (*right) && (*left)->pre && (*left)->pre->color == (*right)->color ||
            (*left) && (*right) && (*right)->next && (*right)->next->color == (*left)->color ||
            (*left) && (*left)->pre && (*left)->pre->pre && (*left)->pre->color == (*left)->color && (*left)->pre->pre->color == (*left)->color ||
            (*right) && (*right)->next && (*right)->next->next && (*right)->next->color == (*right)->color && (*right)->next->next->color == (*right)->color)
        {
            char c = (*left) ? (*left)->color : (*right)->color;
            while((*left) && (*left)->color == c)
            {
                *left = (*left)->pre;
            }
            while((*right) && (*right)->color == c)
            {
                *right = (*right)->next;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

void deleteAllSame(Chain *chain, Ball *ball)
{
    Ball *left = 0, *right = 0, *del, *tmp;
    if(ball->pre && ball->pre->color == ball->color)
    {
        left = ball->pre;
        right = ball;
    }
    else if(ball->next && ball->next->color == ball->color)
    {
        left = ball;
        right = ball->next;
    }
    else
    {
        return;
    }
    if(deleteAllSameTogether(chain, &left, &right))
    {
        if(!left && !right)
        {
            del = chain->ball;
            chain->ball = 0;
        }
        else
        {
            del = left ? left->next : chain->ball;
            right->pre->next = 0;
            right->pre = left;
            if(left)
            {
                left->next = right;
            }
            else
            {
                chain->ball = right;
            }
        }
        while(del)
        {
            tmp = del;
            del = del->next;
            free(tmp);
        }
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
