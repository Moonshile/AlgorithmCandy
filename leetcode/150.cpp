class Solution {
private:
    inline bool isOperator(string s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
    
    inline int compute(string op, int v1, int v2) {
        if (op == "+") {
            return v1 + v2;
        } else if (op == "-") {
            return v1 - v2;
        } else if (op == "*") {
            return v1*v2;
        } else {
            return v1/v2;
        }
    }
    
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (auto &t: tokens) {
            if (!isOperator(t)) {
                s.push(atoi(t.c_str()));
            } else {
                int v2 = s.top();
                s.pop();
                int v1 = s.top();
                s.pop();
                s.push(compute(t, v1, v2));
            }
        }
        return s.top();
    }
};
