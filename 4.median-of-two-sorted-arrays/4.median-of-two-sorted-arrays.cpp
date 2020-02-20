// 4.median-of-two-sorted-arrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/

/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:

	double median(const vector<int>& nums) {
		if (nums.size() == 1) { return nums[0]; }
		auto half = nums.size() / 2;
		if (nums.size() % 2 == 0) {
			return (nums[half - 1] + nums[half]) / 2.0;
		} else {
			return nums[half];
		}
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.empty()) { return median(nums2); }
		if (nums2.empty()) { return median(nums1); }

		auto max_len = (nums1.size() + nums2.size());
		vector<int> nums;
		nums.reserve(max_len);
		for (size_t n = 0, i = 0, j = 0; n < max_len; n++) {
			if (i < nums1.size() && j < nums2.size()) {
				int x = nums1[i];
				int y = nums2[j];
				if (x < y) {
					nums.push_back(x);
					i++;
				} else if (x == y) {
					nums.push_back(x);
					nums.push_back(x);
					i++;
					j++;
				} else {
					nums.push_back(y);
					j++;
				}
			} else if (i < nums1.size()) {
				while (i < nums1.size()) {
					nums.push_back(nums1[i++]);
				}
			} else if (j < nums2.size()) {
				while (j < nums2.size()) {
					nums.push_back(nums2[j++]);
				}
			} else {
				break;
			}
		}

		return median(nums);
	}

	bool test(vector<int> nums1, vector<int> nums2, double expected_median) {
		return findMedianSortedArrays(nums1, nums2) == expected_median;
	}
};

int main()
{
	Solution s;
	assert(s.test({ 1, 3 }, { 2 }, 2.0));

	assert(s.test({ 1, 2 }, { 3, 4 }, 2.5));

	assert(s.test({ 1 }, { 1 }, 1));

	assert(s.test({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4 }, 
				  { 1, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4 }, 
				  3));

	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
