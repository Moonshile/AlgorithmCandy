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

int main()
{
    int list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1}
    }, i, j;
    for(i = 0; i < 3; i++)
    {
        msort(list[i], 0, 8);
        for(j = 0; j < 9; j++)
        {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
