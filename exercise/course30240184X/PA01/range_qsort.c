#include<stdlib.h>
#include<stdio.h>


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

#define M (500000)
#define CUTOFF (3)

typedef int LIST_TYPE;

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
    read_from_stdin();
    next_int(&n);
    next_int(&m);
    points = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++)
    {
        next_int(points + i);
    }
    myQsort(points, 0, n - 1, &compare);
    for(i = 0; i < m; i++)
    {
        next_int(&a);
        next_int(&b);
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
