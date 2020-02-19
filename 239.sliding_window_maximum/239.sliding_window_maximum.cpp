#include <vector>
#include <assert.h>
#include <queue>
#include <list>

using namespace std;


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


vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    vector<int> r;
    if (nums.empty()) { return r; }
    MaxQueue q;
    for (int i = 0; i < k && i < nums.size(); i++) {
        q.push(nums[i]);
    }
    if (!q.empty()) {
        r.push_back(q.getMax());
    }
    for (int i = k; i < nums.size(); i++) {
        q.pop();
        q.push(nums[i]);
        r.push_back(q.getMax());
    }
    return r;
}

int main() {
    assert(maxSlidingWindow({ 1,3,-1,-3,5,3,6,7 }, 3) == vector<int>({}));
}