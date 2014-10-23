#include <stdio.h>
#include <stdlib.h>

typedef int LIST_TYPE;

int find(LIST_TYPE *list, int n, LIST_TYPE value, int (*cmp)(const void*, const void *))
{
     int start = 0, end = n - 1, mid = (start + end)/2;
     while((*cmp)((const void *)list[mid], (const void *)value) != 0)
     {
         if(start >= end)
         {
             return -1;
         }
         if((*cmp)((const void *)list[mid], (const void *)value) < 0)
         {
             start = mid + 1;
         }
         else
         {
             end = mid - 1;
         }
         mid = (start + end)/2;
     }
     return mid;
}

int compare(const void *a, const void *b)
{
    return (int)((long)a - (long)b);
}

int main()
{
    LIST_TYPE list[] = {1,2,3,4,5,6,7,8,9};
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("%d ", find(list, 9, i, &compare));
    }
    putchar('\n');
}
