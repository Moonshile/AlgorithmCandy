#include<stdlib.h>
#include<stdio.h>

#define M (500000)

typedef int LIST_TYPE;

void reverse(LIST_TYPE *list, int start, int end)
{
    while(end > start)
    {
        LIST_TYPE tmp = list[start];
        list[start] = list[end];
        list[end] = tmp;
        start++;
        end--;
    }
}

void shift(LIST_TYPE *list, int start, int mid, int end)
{
    reverse(list, start, mid - 1);
    reverse(list, mid, end);
    reverse(list, start, end);
}

void merge(LIST_TYPE *list, int start, int mid, int end, int (*cmp)(const void*, const void *))
{
    int i = start, j = mid, old_j;
    while(i < j && j <= end){
        old_j = j;
        // i<j must be tested first
        while(i < j && (*cmp)((const void*)list[i], (const void*)list[j]) <= 0)
        {
            i++;
        }
        // j<=end must be tested first
        while(j <= end && (*cmp)((const void*)list[j], (const void*)list[i]) < 0)
        {
            j++;
        }
        shift(list, i, old_j, j - 1);
        i += j - old_j;
    }
}

void msort(LIST_TYPE *list, int start, int end, int (*cmp)(const void*, const void *))
{
    if(start < end)
    {
        int mid = (start + end)/2;
        msort(list, start, mid, cmp);
        msort(list, mid + 1, end, cmp);
        merge(list, start, mid + 1, end, cmp);
    }
}

int compare(const void *x, const void *y)
{
    return (int)((long)x - (long)y);
}

int find(int *list, int n, int value, int *l, int *r)
{
     int start = 0, end = n - 1, mid = (start + end)/2;
     while(list[mid] != value)
     {
         if(start >= end)
         {
             *l = list[mid] > value ? mid - 1 : mid;
             *r = list[mid] > value ? mid : mid + 1;
             return -1;
         }
         if(list[mid] < value)
         {
             start = mid + 1;
         }
         else
         {
             end = mid - 1;
         }
         mid = (start + end)/2;
     }
     *l = mid;
     *r = mid;
     return mid;
}

int main()
{
    int n, m, i, j, a, b, la, ra, lb, rb;
    LIST_TYPE *points;
    scanf("%d %d", &n, &m);
    points = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", points + i);
    }
    msort(points, 0, n - 1, &compare);
    for(i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        a = find(points, n, a, &la, &ra);
        b = find(points, n, b, &lb, &rb);
        if(la < 0 && lb < 0 || ra > n- 1 && rb > n - 1)
        {
            printf("0\n");
        }
        else
        {
            a = a < 0 ? ra : a;
            b = b < 0 ? lb : b;
            printf("%d\n", b - a + 1);
        }
    }
    free(points);
    return 0;
}
