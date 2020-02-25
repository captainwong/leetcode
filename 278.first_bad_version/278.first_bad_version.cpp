#include <stdio.h>
#include <assert.h>

using namespace std;


bool isBadVersion(int version) {
    return version >= 4;
}

/*
执行用时 :4 ms, 在所有 C++ 提交中击败了63.15%的用户
内存消耗 :8.5 MB, 在所有 C++ 提交中击败了5.70%的用户
*/
namespace solution1 {
int binSearch(int l, int r) {
    if (r - l < 1) { return l; }
    int m = l + ((r - l) >> 1);
    if (isBadVersion(m)) {
        return binSearch(l, m);
    } else {
        return binSearch(m + 1, r);
    }
}

int firstBadVersion(int n) {
    return binSearch(1, n);
}
}


/*
执行用时 :0 ms, 在所有 C++ 提交中击败了100.00%的用户
内存消耗 :8.3 MB, 在所有 C++ 提交中击败了5.70%的用户
*/
namespace solution2 {
int firstBadVersion(int n) {
    int l = 1, r = n;
    while (l < r) {
        int m = l + ((r - l) >> 1);
        if (isBadVersion(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}
}


int main()
{
    assert(solution1::firstBadVersion(5) == 4);
    assert(solution2::firstBadVersion(5) == 4);
}