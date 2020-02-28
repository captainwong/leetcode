#include <assert.h>

/*
ִ����ʱ :4 ms, ������ C++ �ύ�л�����64.05%���û�
�ڴ����� :8 MB, ������ C++ �ύ�л�����72.01%���û�
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
ִ����ʱ :0 ms, ������ C++ �ύ�л�����100.00%���û�
�ڴ����� :8.2 MB, ������ C++ �ύ�л�����6.38%���û�
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