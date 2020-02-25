#include <stdio.h>
#include <assert.h>

using namespace std;


bool isBadVersion(int version) {
    return version >= 4;
}

/*
ִ����ʱ :4 ms, ������ C++ �ύ�л�����63.15%���û�
�ڴ����� :8.5 MB, ������ C++ �ύ�л�����5.70%���û�
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
ִ����ʱ :0 ms, ������ C++ �ύ�л�����100.00%���û�
�ڴ����� :8.3 MB, ������ C++ �ύ�л�����5.70%���û�
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