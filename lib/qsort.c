#include <stdio.h>
#include <stdlib.h>

typedef int LIST_TYPE;

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

int compare(const void *x, const void *y)
{
    return (int)((long)x - (long)y);
}

int main()
{
    LIST_TYPE list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1}
    }, i, j;
    for(i = 0; i < 3; i++)
    {
        myQsort(list[i], 0, 8, &compare);
        for(j = 0; j < 9; j++)
        {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
