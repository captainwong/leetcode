#include <vector>
#include <assert.h>
#include <stack>
#include <unordered_map>

using namespace std;

vector<int> nextGreaterElements(const vector<int>& nums) {
    stack<int> s;
    unordered_map<int, int> nextGreater;
    for (auto n : nums) {
        while (!s.empty() && s.top() < n && (nextGreater.find(s.top()) == nextGreater.end())) {
            nextGreater[s.top()] = n;
            s.pop();
        }
        if (nextGreater.find(n) == nextGreater.end()) {
            s.push(n);
        }
    }
    for (auto n : nums) {
        while (!s.empty() && s.top() < n && (nextGreater.find(s.top()) == nextGreater.end())) {
            nextGreater[s.top()] = n;
            s.pop();
        }
        if (s.empty()) {
            break;
        }
    }
    while (!s.empty()) {
        nextGreater[s.top()] = -1;
        s.pop();
    }
    vector<int> r;
    for (auto n : nums) {
        r.push_back(nextGreater[n]);
    }
    return r;
}

int main()
{
    assert(nextGreaterElements({ 100,1,11,1,120,111,123,1,-1,-100 }) == vector<int>({ 120,11,120,120,123,123,-1,100,100,100 }));
}