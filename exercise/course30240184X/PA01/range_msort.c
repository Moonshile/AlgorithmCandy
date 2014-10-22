#include<stdlib.h>
#include<stdio.h>

#define M (500000)

void reverse(int *list, int start, int end)
{
    while(end > start)
    {
        int tmp = list[start];
        list[start] = list[end];
        list[end] = tmp;
        start++;
        end--;
    }
}

void shift(int *list, int start, int mid, int end)
{
    reverse(list, start, mid - 1);
    reverse(list, mid, end);
    reverse(list, start, end);
}

void merge(int *list, int start, int mid, int end)
{
    int i = start, j = mid, old_j;
    while(i < j && j <= end){
        old_j = j;
        while(list[i] <= list[j] && i < j)
        {
            i++;
        }
        while(list[j] < list[i] && j <= end)
        {
            j++;
        }
        shift(list, i, old_j, j - 1);
        i += j - old_j;
    }
}

void msort(int *list, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end)/2;
        sort(list, start, mid);
        sort(list, mid + 1, end);
        merge(list, start, mid + 1, end);
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
    msort(points, 0, n - 1);
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
