#include <stdio.h>
#include <assert.h>

int d[] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };
int repeat_times = 0;

bool isHappy(int n) {
	int s = 0;
	while (n) {
		s += d[n % 10];
		n /= 10;
	}
	return ((s > 9) || (++repeat_times < 10)) ? isHappy(s) : (s == 1);
}

int main()
{
	//for (int i = 19; i < 1000; i++) {
	//	//printf("\r%03d/1000", i);
	//	if (isHappy(i)) {
	//		printf("%d\n", i);
	//	} else {
	//		//printf(" false");
	//	}
	//}

	assert(isHappy(1111111));
}