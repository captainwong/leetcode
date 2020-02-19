
#include <vector>
#include <assert.h>
#include <stack>
#include <queue>
#include <list>


using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    bool empty() const {
        return s.empty();
    }

    void push(int x) {
        s.push(x);
        if (m.empty() || m.top() >= x) {
            m.push(x);
        }
    }

    void pop() {
        int x = s.top(); s.pop();
        if (!m.empty() && m.top() == x) {
            m.pop();
        }
    }

    int top() const {
        return s.top();
    }

    int getMin() const {
        return m.top();
    }

    stack<int> s = {};
    stack<int> m = {};
};

class MaxStack {
public:
    /** initialize your data structure here. */
    MaxStack() {

    }

    bool empty() const {
        return s.empty();
    }

    void push(int x) {
        s.push(x);
        if (m.empty() || m.top() <= x) {
            m.push(x);
        }
    }

    void pop() {
        int x = s.top(); s.pop();
        if (!m.empty() && m.top() == x) {
            m.pop();
        }
    }

    int top() const {
        return s.top();
    }

    int getMax() const {
        return m.top();
    }

    stack<int> s = {};
    stack<int> m = {};
};

class MinQueue {
public:
    /** initialize your data structure here. */
    MinQueue() {

    }

    bool empty() const {
        return q.empty();
    }

    void push(int x) {
        q.push(x);
        while (!m.empty() && m.back() > x) {
            m.pop_back();
        }
        m.push_back(x);
    }

    void pop() {
        int x = q.front(); q.pop();
        if (!m.empty() && m.front() == x) {
            m.pop_front();
        }
    }

    int front() const {
        return q.front();
    }

    int getMin() const {
        return m.front();
    }

    queue<int> q = {};
    list<int> m = {};
};


class MaxQueue {
public:
    /** initialize your data structure here. */
    MaxQueue() {

    }

    bool empty() const {
        return q.empty();
    }

    void push(int x) {
        q.push(x);
        while (!m.empty() && m.back() < x) {
            m.pop_back();
        }
        m.push_back(x);
    }

    void pop() {
        int x = q.front(); q.pop();
        if (!m.empty() && m.front() == x) {
            m.pop_front();
        }
    }

    int front() const {
        return q.front();
    }

    int getMax() const {
        return m.front();
    }

    queue<int> q = {};
    list<int> m = {};
};


int main()
{
    {
        MinStack s;
        s.push(2);
        s.push(1);
        s.push(3);
        s.push(4);
        assert(1 == s.getMin());
        s.pop();
        assert(1 == s.getMin());
        s.pop();
        assert(1 == s.getMin());
        s.pop();
        assert(2 == s.getMin());

    }

    {
        MaxStack s;
        s.push(2);
        s.push(1);
        s.push(3);
        s.push(4);
        assert(4 == s.getMax());
        s.pop();
        assert(3 == s.getMax());
        s.pop();
        assert(2 == s.getMax());
        s.pop();
        assert(2 == s.getMax());
    }

    {
        MinQueue s;
        s.push(2);
        s.push(1);
        s.push(3);
        s.push(4);
        assert(1 == s.getMin());
        s.pop();
        assert(1 == s.getMin());
        s.pop();
        assert(3 == s.getMin());
        s.pop();
        assert(4 == s.getMin());

    }

    {
        MaxQueue s;
        s.push(2);
        s.push(1);
        s.push(3);
        s.push(4);
        assert(4 == s.getMax());
        s.pop();
        assert(4 == s.getMax());
        s.pop();
        assert(4 == s.getMax());
        s.pop();
        assert(4 == s.getMax());
    }
}