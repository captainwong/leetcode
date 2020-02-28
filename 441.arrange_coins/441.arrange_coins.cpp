#include <math.h>
#include <assert.h>

int arrangeCoins(int s) {
    if (s == 0) { return 0; } else if (s < 3) { return 1; }
    int l = 2;
    int r = sqrt((long)s * 2);
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        int sum = ((long)m * (m + 1) / 2);
        if (sum < s) {
            l = m + 1;
            continue;
        } else if (sum == s) {
            return m;
        } else {
            r = m - 1;
        }
    }
    if ((long)l * (l + 1) / 2 == s) { return l; }
    return l - 1;
}

int main()
{
    assert(arrangeCoins(4) == 2);
    assert(arrangeCoins(5) == 2);
    assert(arrangeCoins(8) == 3);
}