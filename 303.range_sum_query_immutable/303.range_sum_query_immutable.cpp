#include <stdio.h>
#include <assert.h>
#include <vector>
#include "../common/leetcode.h"

using namespace std;

/*
执行用时 :204 ms, 在所有 C++ 提交中击败了25.48%的用户
内存消耗 :19 MB, 在所有 C++ 提交中击败了6.50%的用户
*/
namespace solution_brute_force {
class NumArray {
public:
    NumArray(vector<int>& nums) {
        this->nums = nums;
    }

    int sumRange(int i, int j) {
        int s = 0;
        while (i < j) {
            s += nums[i++] + nums[j--];
        }
        if (i == j) { s += nums[i]; }
        return s;
    }

    vector<int> nums = {};
};
}


/*
执行用时 :40 ms, 在所有 C++ 提交中击败了51.02%的用户
内存消耗 :18.9 MB, 在所有 C++ 提交中击败了6.63%的用户
*/
namespace solution2 {
class NumArray {
public:
    NumArray(vector<int>& nums) {
        sums.resize(nums.size() + 1);
        sums[0] = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            sums[i + 1] = sums[i] + nums[i];
        }
    }

    int sumRange(int i, int j) {
        return sums[j + 1] - sums[i];
    }

    vector<int> sums = {};
};
}


int main()
{
    auto nums = convertLeetcodeInputToIntVector("[-2,0,3,-5,2,-1]");
    {
        using namespace solution_brute_force;
        NumArray na(nums);
        assert(na.sumRange(0, 2) == 1);
        assert(na.sumRange(2, 5) == -1);
        assert(na.sumRange(0, 5) == -3);
    }

    {
        using namespace solution2;
        NumArray na(nums);
        assert(na.sumRange(0, 2) == 1);
        assert(na.sumRange(2, 5) == -1);
        assert(na.sumRange(0, 5) == -3);
    }
}
