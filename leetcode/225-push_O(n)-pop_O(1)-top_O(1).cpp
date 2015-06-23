// push O(n), pop/top O(1)
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
        helper->push(x);
        while (!container->empty()) {
            helper->push(container->front());
            container->pop();
        }
        swap(container, helper);
    }

    // Removes the element on top of the stack.
    void pop() {
        container->pop();
    }

    // Get the top element.
    int top() {
        return container->front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return container->empty();
    }
};
