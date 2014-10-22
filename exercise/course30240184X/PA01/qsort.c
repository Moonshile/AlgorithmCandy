#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int list[][9] = {
        {1,2,3,4,5,6,7,8,9},
        {9,3,6,4,7,4,2,1,5},
        {9,8,7,6,5,4,3,2,1}
    }, i, j;
    for(i = 0; i < 3; i++)
    {
        myQsort(list[i], 0, 8);
        for(j = 0; j < 9; j++)
        {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
