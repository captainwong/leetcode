#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;


/*
执行用时 :44 ms, 在所有 C++ 提交中击败了28.88%的用户
内存消耗 :9.2 MB, 在所有 C++ 提交中击败了90.27%的用户
*/
namespace solution1 {
class Solution {
public:

    struct U {
        U() {
            list<long> l{ 1 };
            unordered_set<long> s{ 1 };
            long u = 0;
            for (int i = 0; i < 1690; i++) {
                u = l.front();
                r.push_back(u);
                l.pop_front();
                s.erase(u);
                long m2 = u * 2;
                long m3 = u * 3;
                long m5 = u * 5;
                if (s.find(m2) == s.end()) {
                    s.insert(m2);
                    l.push_back(m2);
                }
                if (s.find(m3) == s.end()) {
                    s.insert(m3);
                    l.push_back(m3);
                }
                if (s.find(m5) == s.end()) {
                    s.insert(m5);
                    l.push_back(m5);
                }
                l.sort();
            }
        }

        vector<int> r = {};
    };

    Solution() {

    }

    static U u;

    int nthUglyNumber(int n) {
        return u.r[n - 1];
    }
};

Solution::U Solution::u = {};
}

/*
执行用时 :12 ms, 在所有 C++ 提交中击败了69.58%的用户
内存消耗 :11.9 MB, 在所有 C++ 提交中击败了21.82%的用户
*/
namespace solution2 {

int nthUglyNumber(int n) {
    int i2 = 0, i3 = 0, i5 = 0;
    vector<int> ns = { 1 };
    for (int i = 0; i < n; i++) {
        int u = min(min(ns[i2] * 2, ns[i3] * 3), ns[i5] * 5);
        ns.push_back(u);
        if (u % 2 == 0) { i2++; }
        if (u % 3 == 0) { i3++; }
        if (u % 5 == 0) { i5++; }
    }
    return ns[n - 1];
}

}


/*
执行用时 :4 ms, 在所有 C++ 提交中击败了98.03%的用户
内存消耗 :8.5 MB, 在所有 C++ 提交中击败了91.84%的用户
*/
namespace solution3 {

class Solution {
public:
    struct U {
        vector<int> ns = { 1 };
        U() {
            int i2 = 0, i3 = 0, i5 = 0;
            for (int i = 0; i < 1690; i++) {
                int u = min(min(ns[i2] * 2, ns[i3] * 3), ns[i5] * 5);
                ns.push_back(u);
                if (u % 2 == 0) { i2++; }
                if (u % 3 == 0) { i3++; }
                if (u % 5 == 0) { i5++; }
            }
        }
    };

    int nthUglyNumber(int n) {        
        return u.ns[n - 1];
    }

    static U u;
};

Solution::U Solution::u = {};

}

int main()
{
    assert(solution1::Solution().nthUglyNumber(10) == 12);
    assert(solution2::nthUglyNumber(10) == 12);
    assert(solution3::Solution().nthUglyNumber(10) == 12);
}