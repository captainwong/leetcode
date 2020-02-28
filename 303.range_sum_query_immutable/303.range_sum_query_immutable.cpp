#include <stdio.h>
#include <assert.h>
#include <vector>
#include "../common/leetcode.h"

using namespace std;

/*
ִ����ʱ :204 ms, ������ C++ �ύ�л�����25.48%���û�
�ڴ����� :19 MB, ������ C++ �ύ�л�����6.50%���û�
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
ִ����ʱ :40 ms, ������ C++ �ύ�л�����51.02%���û�
�ڴ����� :18.9 MB, ������ C++ �ύ�л�����6.63%���û�
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
