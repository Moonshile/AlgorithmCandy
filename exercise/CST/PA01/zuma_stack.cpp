#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);
char next_char();

#define MAX_COUNT (20000)

class Stack {
public:
	Stack();
	bool empty();
	void push(char);
	char pop();
	char top();
    int size();
    // forward: copy from left to right if true, else from right to left
    void toString(char* buf, int buf_sz, bool forward);
private:
    char _stack[MAX_COUNT];
    int _top;
};

Stack::Stack() {
    _top = 0;
}

bool Stack::empty() {
    return _top == 0;
}

void Stack::push(char value) {
    _stack[_top++] = value;
}

char Stack::pop() {
    return _stack[--_top];
}

char Stack::top() {
    return _stack[_top - 1];
}

int Stack::size() {
    return _top;
}

void Stack::toString(char* buf, int buf_sz, bool forward) {
    if(forward) {
        strncpy(buf, _stack, _top);
    } else {
        for(int i = _top - 1, j = 0; i >= 0; i--, j++) {
            buf[j] = _stack[i];
        }
    }
}

class CountStack {
public:
    CountStack() {}
	bool empty();
	void push(char);
	char pop();
	char top();
    int count();
    int size();
    void toString(char* buf, int buf_sz, bool forward);
private:
    Stack _stack;
    Stack _count;
};

bool CountStack::empty() {
    return _stack.empty();
}

void CountStack::push(char value) {
    if(_count.empty() || value != _stack.top()) {
        _count.push(1);
    } else {
        _count.push(_count.top() + 1);
    }
    // must push into _stack AFTER push into _count!!!
    _stack.push(value);
}

char CountStack::pop() {
    _count.pop();
    return _stack.pop();
}

char CountStack::top() {
    return _stack.top();
}

int CountStack::count() {
    return _count.top();
}

int CountStack::size() {
    return _stack.size();
}

void CountStack::toString(char* buf, int buf_sz, bool forward) {
    _stack.toString(buf, buf_sz, forward);
}

class Zuma {
public:
    Zuma() {}
    void insert(int i, char value);
    void eliminate();
    int toString(char* buf, int buf_sz);
private:
    CountStack _pre;
    CountStack _next;
};

void Zuma::insert(int i, char value) {
    for(int j = _pre.size(); j < i; j++) {
        _pre.push(_next.pop());
    }
    for(int j = _pre.size(); j > i; j--) {
        _next.push(_pre.pop());
    }
    _pre.push(value);
}

void Zuma::eliminate() {
    while(true) {
        while(_next.size() > 0 && _next.top() == _pre.top()) {
            _pre.push(_next.pop());
        }
        if(_pre.count() < 3) {
            break;
        }
        for(int i = _pre.count(); i > 0; i--) {
            _pre.pop();
        }
    }
}

int Zuma::toString(char* buf, int buf_sz) {
    int i = 0;
    if(_pre.size() + _next.size() == 0) {
        buf[i++] = '-';
        buf[i++] = '\n';
        return 2;
    }
    _pre.toString(buf + i, buf_sz - i, true);
    i += _pre.size();
    _next.toString(buf + i, buf_sz - i, false);
    i += _next.size();
    buf[i++] = '\n';
    return _pre.size() + _next.size() + 1;
}

#define MAX_LEN (10<<20)
char outs[MAX_LEN];

int main(){
    Zuma* zuma = new Zuma();
    int i = 0, n, j, oi = 0;
    char* buf = reset_io(), c;
    while((c = next_char()) != '\n') {
        zuma->insert(i++, c);
    }
    next_int(&n);
    for(i = 0; i < n; i++) {
        next_int(&j);
        c = next_char();
        zuma->insert(j, c);
        zuma->eliminate();
        oi += zuma->toString(outs + oi, MAX_LEN);
        if(oi >= 9<<20) {
            outs[oi++] = 0;
            printf("%s", outs);
            oi = 0;
        }
    }
    outs[oi++] = 0;
    printf("%s", outs);
    free(buf);
    return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (10<<20)
#define OUT_BUF_SIZE (10<<20)

char *fread_buf;
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    fread_buf = (char*)malloc(sizeof(char)*IN_BUF_LEN);
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
    while(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '\0' || c == '\n')) {
        c = fread_buf[fread_buf_pointer++];
    }
    return c;
}
