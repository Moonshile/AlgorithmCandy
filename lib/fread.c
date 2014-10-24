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

char next_char()
{
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0'))
    {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}

int next_str(char *buf)
{
    int i = 0;
    char c = fread_buf[fread_buf_pointer++];
    while(c == ' ' || c == '\n' || c == '\r' || c == '\t')
    {
        c = fread_buf[fread_buf_pointer++];
    }
    while(c != '\n' && c != '\0')
    {
        buf[i] = fread_buf[fread_buf_pointer++];
        c = buf[i++];
    }
    return c;
}

int main()
{
    int n, code;
    read_from_stdin();
    do
    {
        //code = next_int(&n);
        code = next_char();
        printf("%c ", (char)code);
    }while(code);
    return 0;
}
