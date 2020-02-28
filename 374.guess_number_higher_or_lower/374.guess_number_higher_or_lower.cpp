#include <assert.h>

const int pick = 6;

int guess(int n) {
    if (n == pick) { return 0; }
    return n > pick ? -1 : 1;
}

int guessNumber(int n) {
    int l = 1, r = n;
    while (l < r) {
        int m = l + ((r - l) >> 1);
        int g = guess(m);
        if (g == 0) {
            return m;
        } else if (g == -1) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main()
{
    assert(guessNumber(10) == 6);
}