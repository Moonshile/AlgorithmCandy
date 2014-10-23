#include <stdio.h>
#include <stdlib.h>

typedef struct __light__ {
    int x;
    int y;
} Light;

typedef Light* LIST_TYPE;


#define CUTOFF (3)

void swap(LIST_TYPE *list, int a, int b)
{
    LIST_TYPE tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

void sort3(LIST_TYPE *list, int left, int right, int (*cmp)(const void *, const void *))
{
    int mid = (left + right)/2;
    if((*cmp)((const void *)list[left], (const void *)list[mid]) > 0)
    {
        swap(list, left, mid);
    }
    if((*cmp)((const void *)list[left], (const void *)list[right]) > 0)
    {
        swap(list, left, right);
    }
    if((*cmp)((const void *)list[mid], (const void *)list[right]) > 0)
    {
        swap(list, mid, right);
    }
}

LIST_TYPE median3(LIST_TYPE *list, int left, int right, int (*cmp)(const void *, const void *))
{
    int mid = (left + right)/2;
    sort3(list, left, right, cmp);
    swap(list, mid, right - 1);
    return list[right - 1];
}

void myQsort(LIST_TYPE *list, int left, int right, int (*cmp)(const void *, const void *))
{
    int i, j;
    LIST_TYPE pivot;
    if(left + CUTOFF <= right)
    {
        pivot = median3(list, left, right, cmp);
        i = left;
        j = right - 1;
        for(; ; )
        {
            while((*cmp)((const void *)list[++i], (const void *)pivot) < 0){}
            while((*cmp)((const void *)list[--j], (const void *)pivot) > 0){}
            if(i < j)
            {
                swap(list, i, j);
            }
            else
            {
                break;
            }
        }
        swap(list, i, right - 1);
        myQsort(list, left, i - 1, cmp);
        myQsort(list, i + 1, right, cmp);
    }
    else
    {
        sort3(list, left, right, cmp);
    }
}

long long merge(LIST_TYPE *list, LIST_TYPE *tmp, int left, int right, int right_end, int (*cmp)(const void*, const void *))
{
    int i, left_end, num, tmp_pos;
    left_end = right - 1;
    tmp_pos = left;
    num = right_end - left + 1;
    long long res = 0;
    while(left <= left_end && right <= right_end)
    {
        if((*cmp)((const void *)list[left], (const void *)list[right]) <= 0)
        {
            tmp[tmp_pos++] = list[left++];
            res += right_end - right + 1;
        }
        else
        {
            tmp[tmp_pos++] = list[right++];
        }
    }
    while(left <= left_end)
    {
        tmp[tmp_pos++] = list[left++];
    }
    while(right <= right_end)
    {
        tmp[tmp_pos++] = list[right++];
    }
    for(i = 0; i < num; i++, right_end--)
    {
        list[right_end] = tmp[right_end];
    }
    return res;
}

long long msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int start, int end, int (*cmp)(const void*, const void *))
{
    if(start < end)
    {
        int mid = (start + end)/2;
        long long a = msort_do(list, tmp, start, mid, cmp);
        long long b = msort_do(list, tmp, mid + 1, end, cmp);
        long long x = merge(list, tmp, start, mid + 1, end, cmp);
        return a + b + x;
    }
    return 0L;
}

long long msort(LIST_TYPE *list, int start, int end, int (*cmp)(const void*, const void *))
{
    long long res;
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(end - start + 1));
    res = msort_do(list, tmp, start, end, cmp);
    free(tmp);
    return res;
}

int compareX(const void *a, const void *b)
{
    return ((LIST_TYPE)a)->x - ((LIST_TYPE)b)->x;
}

int compareY(const void *a, const void *b)
{
    return ((LIST_TYPE)a)->y - ((LIST_TYPE)b)->y;
}

int main()
{
    int i, n, x, y, j;
    LIST_TYPE *lights;
    long long res = 0;
    scanf("%d", &n);
    lights = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        lights[i] = (LIST_TYPE)malloc(sizeof(Light));
        lights[i]->x = x;
        lights[i]->y = y;
    }
    myQsort(lights, 0, n - 1, &compareX);
    res = msort(lights, 0, n - 1, &compareY);
    for(i = 0; i < n; i++)
    {
        free(lights[i]);
    }
    free(lights);
    printf("%lld", res);
    return 0;
}

