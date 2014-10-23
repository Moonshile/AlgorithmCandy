#include<stdlib.h>
#include<stdio.h>

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

int main()
{
    LIST_TYPE list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1},
        {1,2,321,564,6,2135,54,321,321}
    }, i, j;
    for(i = 0; i < 4; i++)
    {
        msort(list[i], 0, 8, &compare);
        for(j = 0; j < 9; j++)
        {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
