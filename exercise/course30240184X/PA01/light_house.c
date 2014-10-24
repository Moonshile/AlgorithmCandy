#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin()
{
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

int next_int(int *res)
{
    *res = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= '0' && c <= '9' || c == '\0'))
    {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0')
    {
        return 0;
    }
    while(c != ' ' && c != '\n' && c != '\0')
    {
        if(c >= '0' && c <= '9')
        {
            *res = (*res)*10 + c - '0';
        }
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

typedef int LIST_TYPE;


#define CUTOFF (3)

void swap(LIST_TYPE *list_x, LIST_TYPE *list_y, int a, int b)
{
    LIST_TYPE tmp = list_x[a];
    list_x[a] = list_x[b];
    list_x[b] = tmp;
    tmp = list_y[a];
    list_y[a] = list_y[b];
    list_y[b] = tmp;
}

void sort3(LIST_TYPE *list_x, LIST_TYPE *list_y, int left, int right)
{
    int mid = (left + right)/2;
    if(list_x[left] > list_x[mid])
    {
        swap(list_x, list_y, left, mid);
    }
    if(list_x[left] > list_x[right])
    {
        swap(list_x, list_y, left, right);
    }
    if(list_x[mid] > list_x[right])
    {
        swap(list_x, list_y, mid, right);
    }
}

LIST_TYPE median3(LIST_TYPE *list_x, LIST_TYPE *list_y, int left, int right)
{
    int mid = (left + right)/2;
    sort3(list_x, list_y, left, right);
    swap(list_x, list_y, mid, right - 1);
    return list_x[right - 1];
}

void myQsort(LIST_TYPE *list_x, LIST_TYPE *list_y, int left, int right)
{
    int i, j;
    LIST_TYPE pivot;
    if(left + CUTOFF <= right)
    {
        pivot = median3(list_x, list_y, left, right);
        i = left;
        j = right - 1;
        for(; ; )
        {
            while(list_x[++i] < pivot){}
            while(list_x[--j] > pivot){}
            if(i < j)
            {
                swap(list_x, list_y, i, j);
            }
            else
            {
                break;
            }
        }
        swap(list_x, list_y, i, right - 1);
        myQsort(list_x, list_y, left, i - 1);
        myQsort(list_x, list_y, i + 1, right);
    }
    else
    {
        sort3(list_x, list_y, left, right);
    }
}

long long merge(LIST_TYPE *list, LIST_TYPE *tmp, int left, int right, int right_end)
{
    int i, left_end, num, tmp_pos;
    left_end = right - 1;
    tmp_pos = left;
    num = right_end - left + 1;
    long long res = 0;
    while(left <= left_end && right <= right_end)
    {
        if(list[left] < list[right])
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

long long msort_do(LIST_TYPE *list, LIST_TYPE *tmp, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end)/2;
        long long a = msort_do(list, tmp, start, mid);
        long long b = msort_do(list, tmp, mid + 1, end);
        long long x = merge(list, tmp, start, mid + 1, end);
        return a + b + x;
    }
    return 0L;
}

long long msort(LIST_TYPE *list, int start, int end)
{
    long long res;
    LIST_TYPE *tmp = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*(end - start + 1));
    res = msort_do(list, tmp, start, end);
    free(tmp);
    return res;
}

int main()
{
    int i, n, x, y, j;
    LIST_TYPE *lights_x, *lights_y;
    long long res = 0;
    read_from_stdin();
    next_int(&n);
    lights_x = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    lights_y = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)*n);
    for(i = 0; i < n; i++)
    {
        next_int(&x);
        next_int(&y);
        lights_x[i] = x;
        lights_y[i] = y;
    }
    myQsort(lights_x, lights_y, 0, n - 1);
    free(lights_x);
    res = msort(lights_y, 0, n - 1);
    free(lights_y);
    printf("%lld", res);
    return 0;
}

