#include<stdlib.h>
#include<stdio.h>

typedef int LIST_TYPE;

void merge(LIST_TYPE *list, LIST_TYPE *tmp, int left, int right, int right_end, int (*cmp)(const void*, const void *))
{
    int i, left_end, num, tmp_pos;
    left_end = right - 1;
    tmp_pos = left;
    num = right_end - left + 1;
    
    while(left <= left_end && right <= right_end)
    {
        if((*cmp)((const void *)list[left], (const void *)list[right]) <= 0)
        {
            tmp[tmp_pos++] = list[left++];
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
}

void msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int start, int end, int (*cmp)(const void*, const void *))
{
    if(start < end)
    {
        int mid = (start + end)/2;
        msort_do(list, tmp, start, mid, cmp);
        msort_do(list, tmp, mid + 1, end, cmp);
        merge(list, tmp, start, mid + 1, end, cmp);
    }
}

void msort(LIST_TYPE *list, int start, int end, int (*cmp)(const void*, const void *))
{
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(end - start + 1));
    msort_do(list, tmp, start, end, cmp);
    free(tmp);
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
