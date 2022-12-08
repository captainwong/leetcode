#include <stdio.h>
#include <stdlib.h>


int isSdn(int n) {
    if (n == 0) { return 0; }
    int N = n;
    while (N) {
        int m = N % 10;
        if (m == 0) { return 0; }
        if (n % m) { return 0; }
        N /= 10;
    }
    return 1;
}

int* selfDividingNumbers(int left, int right, int* returnSize) {
    *returnSize = 0;
    int* RES = malloc(10000 * sizeof(int));
    while (left <= right) {
        if (isSdn(left)) {
            RES[(*returnSize)++] = left;
        }
        left++;
    }
    return RES;
}

int main()
{
    int n;
    int* v = selfDividingNumbers(1, 22, &n);
}