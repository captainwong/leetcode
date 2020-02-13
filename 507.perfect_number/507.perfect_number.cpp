#include <math.h>
#include <assert.h>

bool checkPerfectNumber(int num) {
    int m = sqrt(num);
    int sum = 1;
    for (int i = 2; i < m; i++) {
        int n = num / i;
        if (num % i == 0) {
            sum += n + i;
        }
    }
    if (m * m == num) {
        sum += m;
    }
    return sum == num;
}

int main()
{
    assert(checkPerfectNumber(28));
}