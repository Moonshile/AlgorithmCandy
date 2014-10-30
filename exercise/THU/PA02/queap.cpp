#include <stdio.h>
#include <stdlib.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();

#define MAX_COUNT (1000000)

class Stack
{
public:
	Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
    int _stack[MAX_COUNT];
    int _top;
};

Stack::Stack()
{
    _top = 0;
}

bool Stack::empty()
{
    return _top == 0;
}

void Stack::push(int value)
{
    _stack[_top++] = value;
}

int Stack::pop()
{
    return _stack[--_top];
}

int Stack::top()
{
    return _stack[_top - 1];
}

class MinStack
{
public:
    MinStack();
	bool empty();
	void push(int);
	int pop();
	int top();
    int min();
private:
    Stack _stack;
    Stack _min;
};

MinStack::MinStack()
{
}

bool MinStack::empty()
{
    return _stack.empty();
}

void MinStack::push(int value)
{
    _stack.push(value);
    if(_min.empty() || value < _min.top())
    {
        _min.push(value);
    }
    else
    {
        _min.push(_min.top());
    }
}

int MinStack::pop()
{
    _min.pop();
    return _stack.pop();
}

int MinStack::top()
{
    return _stack.top();
}

int MinStack::min()
{
    return _min.top();
}

class Queap
{
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
    MinStack _stackEn;
    MinStack _stackDe;
};

Queap::Queap()
{
}

void Queap::enqueap(int value)
{
    _stackEn.push(value);
}

int Queap::dequeap()
{
    if(_stackDe.empty())
    {
        while(!_stackEn.empty())
        {
            _stackDe.push(_stackEn.pop());
        }
    }
    return _stackDe.pop();
}

int Queap::min()
{
    if(!(_stackDe.empty() || _stackEn.empty()))
    {
        return _stackEn.min() <= _stackDe.min() ? _stackEn.min() : _stackDe.min();
    }
    if(!_stackDe.empty())
    {
        return _stackDe.min();
    }
    return _stackEn.min();
}

int main()
{
    int n, x;
    char ch;
    Queap* queap = new Queap();
    reset_io();
    next_int(&n);
    for(int i = 0; i < n; i++)
    {
        ch = next_char();
        switch(ch)
        {
        case 'E':
            next_int(&x);
            queap->enqueap(x);
            break;
        case 'D':
            printf("%d\n", queap->dequeap());
            break;
        default: // M
            printf("%d\n", queap->min());
            break;
        }
    }
    delete queap;
	return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (100<<10<<10)
#define OUT_BUF_SIZE (100<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
    char c = fread_buf[fread_buf_pointer++];
    int is_pos = 1;
    while(!(c >= '0' && c <= '9' || c == '\0' || c == '-')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    if(c == '-') {
        is_pos = 0;
        c = fread_buf[fread_buf_pointer++];
    }
    *res = 0;
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    if(!is_pos) {
        *res = -*res;
    }
    return c;
}

// next char, only a-zA-Z
char next_char() {
    char c = fread_buf[fread_buf_pointer++];
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
