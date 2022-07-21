// 1.two-sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if 1
#include <stdlib.h>

#if 0

/*
执行用时：80 ms, 在所有 C 提交中击败了71.77%的用户
内存消耗：6.2 MB, 在所有 C 提交中击败了72.36%的用户
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int* arr = (int*)malloc(sizeof(int) * 2);
                if (!arr) { return NULL; }
                arr[0] = i;
                arr[1] = j;
                *returnSize = 2;
                return arr;
            }
        }
    }
    return NULL;
}

int main()
{

}

#else

// TODO: use hash table

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    
    return NULL;
}

int main()
{

}
#endif

#else
#include <iostream>

// https://leetcode-cn.com/problems/two-sum/

/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> ret;
		unordered_map<int, int> um;
		for (int i = 0; i < nums.size(); i++) {
			auto iter = um.find(target - nums[i]);
			if (iter == um.end()) {
				um.insert(make_pair(nums[i], i));
			} else if (iter->second != i) {
				ret.push_back(i);
				ret.push_back(iter->second);
				break;
			}
		}
		return ret;
	}
};


int main()
{
    
}
#endif
