class MinStack {
private:
    stack<int> s;
    stack<int> m;
    
public:
    void push(int x) {
        s.push(x);
        m.push(m.size() == 0 ? x : min(x, m.top()));
    }

    void pop() {
        s.pop();
        m.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return m.top();
    }
};
