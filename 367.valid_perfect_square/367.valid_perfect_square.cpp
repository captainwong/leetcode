#include <assert.h>

/*
执行用时 :4 ms, 在所有 C++ 提交中击败了64.05%的用户
内存消耗 :8 MB, 在所有 C++ 提交中击败了72.01%的用户
*/
namespace solution_bin {
bool isPerfectSquare(int num) {
    if (num < 2) { return true; }
    int l = 2, r = num / 2;
    while (l <= r) {
        long m = l + (r - l) / 2;
        long x = m * m;
        if (x == num) { return true; } else if (x > num) { r = m - 1; } else { l = m + 1; }
    }
    return false;
}
}


/*
执行用时 :0 ms, 在所有 C++ 提交中击败了100.00%的用户
内存消耗 :8.2 MB, 在所有 C++ 提交中击败了6.38%的用户
*/
namespace solution_newton {

bool isPerfectSquare(int num) {
    if (num < 2) { return true; }
    int x = num / 2;
    while (x * x > num) {
        x = (x + num / x) / 2;
    }
    return x * x == num;
}

}


int main()
{

}