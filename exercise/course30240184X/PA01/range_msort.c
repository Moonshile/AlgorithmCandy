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
    read_from_stdin();
    next_int(&n);
    next_int(&m);
    points = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++)
    {
        next_int(points + i);
    }
    msort(points, 0, n - 1, &compare);
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
