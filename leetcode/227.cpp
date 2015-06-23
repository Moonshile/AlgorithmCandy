class Calculator {
private:
    inline int priority(char op) {
        switch (op) {
            case '+':
            case '-': return 0;
            case '*':
            case '/': return 1;
            case '(': return INT_MAX;
            default: return -1;
        }
    }

    string convertToRPN(string &s) {
        stringstream ss;
        stack<char> op;
        for (char c: s) {
            if (isspace(c) || isdigit(c)) {
                ss << c;
            } else {
                ss << ' ';
                if (c == ')') {
                    while (op.top() != '(') {
                        ss << ' ' << op.top();
                        op.pop();
                    }
                    op.pop();
                } else if (!op.empty() && priority(c) <= priority(op.top())) {
                    while (!op.empty() && op.top() != '(' && priority(c) <= priority(op.top())) {
                        ss << ' ' << op.top();
                        op.pop();
                    }
                    op.push(c);
                } else {
                    op.push(c);
                }
            }
        }
        while (!op.empty()) {
            ss << ' ' << op.top();
            op.pop();
        }
        return ss.str();
    }
    
    int nextInt(string &s, int &i) {
        int res = 0;
        while (isdigit(s[i])) {
            res = res*10 + s[i++] - '0';
        }
        return res;
    }

public:
    int eval(string &s) {
        auto rpn = convertToRPN(s);
        stack<int> res;
        for (int i = 0; i < rpn.size(); ++i) {
            if (isspace(rpn[i])) {
                continue;
            } else if (isdigit(rpn[i])) {
                res.push(nextInt(rpn, i));
                --i;
            } else {
                int v2 = res.top();
                res.pop();
                int v1 = res.top();
                res.pop();
                switch (rpn[i]) {
                    case '+': res.push(v1 + v2); break;
                    case '-': res.push(v1 - v2); break;
                    case '*': res.push(v1*v2); break;
                    case '/':
                    default: res.push(v1/v2); break;
                }
            }
        }
        return res.top();
    }
};

class Solution {
public:
    int calculate(string s) {
        Calculator c;
        return c.eval(s);
    }
};
