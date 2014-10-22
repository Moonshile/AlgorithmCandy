#include<stdlib.h>
#include<stdio.h>

#define M (500000)
#define CUTOFF (3)

void swap(int *list, int a, int b)
{
    int tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

void sort3(int *list, int left, int right)
{
    int mid = (left + right)/2;
    if(list[left] > list[mid])
    {
        swap(list, left, mid);
    }
    if(list[left] > list[right])
    {
        swap(list, left, right);
    }
    if(list[mid] > list[right])
    {
        swap(list, mid, right);
    }
}

int median3(int *list, int left, int right)
{
    int mid = (left + right)/2;
    sort3(list, left, right);
    swap(list, mid, right - 1);
    return list[right - 1];
}

int myQsort(int *list, int left, int right)
{
    int i, j, pivot;
    if(left + CUTOFF <= right)
    {
        pivot = median3(list, left, right);
        i = left;
        j = right - 1;
        for(; ; )
        {
            while(list[++i] < pivot){}
            while(list[--j] > pivot){}
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
        myQsort(list, left, i - 1);
        myQsort(list, i + 1, right);
    }
    else
    {
        sort3(list, left, right);
    }
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
    int n, m, i, j, *points, a, b, la, ra, lb, rb;
    scanf("%d %d", &n, &m);
    points = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", points + i);
    }
    myQsort(points, 0, n - 1);
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
