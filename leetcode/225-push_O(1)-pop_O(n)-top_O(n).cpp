class Stack {
private:
    queue<int> q1;
    queue<int> q2;
    queue<int> *container;
    queue<int> *helper;
    
public:
    Stack(): q1(), q2(), container(&q1), helper(&q2) {}

    // Push element x onto stack.
    void push(int x) {
        container->push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        while (container->size() > 1) {
            helper->push(container->front());
            container->pop();
        }
        container->pop();
        swap(container, helper);
    }

    // Get the top element.
    int top() {
        while (container->size() > 1) {
            helper->push(container->front());
            container->pop();
        }
        int res = container->front();
        helper->push(res);
        container->pop();
        swap(container, helper);
        return res;
    }

    // Return whether the stack is empty.
    bool empty() {
        return container->empty();
    }
};
