#include <stdio.h>
#include <stdlib.h>

char *read_from_stdin();
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

class Queap
{
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
    Stack _stackMain;
    Stack _stackHelp;
    int _size;
    int _min;
    void trans(Stack* out, Stack* in, int n);
    void updateMin();
};

Queap::Queap()
{
    _size = 0;
    _min = 0;
}

void Queap::trans(Stack* out, Stack* in, int n)
{
    for(int i = 0; i < n; i++)
    {
        in->push(out->pop());
    }
}

void Queap::updateMin()
{
    if(_size == 0)
    {
        return;
    }
    Stack* _out = _stackHelp.empty() ? &_stackMain : &_stackHelp;
    Stack* _in = _stackHelp.empty() ? &_stackHelp : &_stackMain;
    int tmp = 0;
    _min = _out->pop();
    _in->push(_min);
    for(int i = 1; i < _size; i++)
    {
        tmp = _out->pop();
        _min = tmp < _min ? tmp : _min;
        _in->push(tmp);
    }
    trans(_in, _out, _size);
}

void Queap::enqueap(int value)
{
    _min = _size == 0 ? value : (value < _min ? value : _min);
    if(_stackMain.empty())
    {
        trans(&_stackHelp, &_stackMain, _size);
    }
    _stackMain.push(value);
    _size++;
}

int Queap::dequeap()
{
    if(_stackHelp.empty())
    {
        trans(&_stackMain, &_stackHelp, _size);
    }
    int res = _stackHelp.pop();
    _size--;
    if(res == _min)
    {
        updateMin();
    }
    return res;
}

int Queap::min()
{
    return _min;
}

int main()
{
    int n, x;
    char ch;
    Queap queap;
    read_from_stdin();
    next_int(&n);
    for(int i = 0; i < n; i++)
    {
        ch = next_char();
        switch(ch)
        {
        case 'E':
            next_int(&x);
            queap.enqueap(x);
            break;
        case 'D':
            printf("%d\n", queap.dequeap());
            break;
        default: // M
            printf("%d\n", queap.min());
            break;
        }
    }
	return 0;
}


#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
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
