#include "../common/leetcode.h"


int maximumProduct(vector<int>& nums) {
    int max1, max2, max3, min1, min2;
    max1 = max2 = max3 = INT_MIN;
    min1 = min2 = INT_MAX;
    for (auto& a : nums) {
        if (a > max1) {
            max3 = max2;
            max2 = max1;
            max1 = a;
        } else if (a > max2) {
            max3 = max2;
            max2 = a;
        } else if (a > max3) {
            max3 = a;
        }

        if (a < min1) {
            min2 = min1;
            min1 = a;
        } else if (a < min2) {
            min2 = a;
        }
    }

    return max(max1 * max2 * max3, min1 * min2 * max1);
}


int main()
{
    auto v = convertLeetcodeInputToIntVector("[-1,-2,-3]");
    printf("%d\n", maximumProduct(v));
}