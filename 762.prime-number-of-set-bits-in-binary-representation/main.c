#include <stdio.h>

static const int PRIME_32[32] = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };

int count1s(int n) {
	int res = 0;
	while (n > 0) {
		res++;
		n &= (n - 1);
	}
	return res;
}

int countPrimeSetBits(int left, int right) {
	int n = 0;
	while (left <= right) {
		if (PRIME_32[count1s(left++)]) {
			n++;
		}
	}
	return n;
}

int main()
{

}