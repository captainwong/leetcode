// 3.longest-substring-without-repeating-characters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
			 Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include "pch.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

	int isContain(string s, char c) {
		int i = 0;
		for (auto _c : s) {
			if (_c == c) { return i; }
			i++;
		}
		return -1;
	}

	int lengthOfLongestSubstring(string s) {
		string sub_bk;
		string sub;
		for (auto c : s) {
			int pos = isContain(sub, c);
			if (pos != -1) {
				if (sub.size() > sub_bk.size()) {
					sub_bk = sub;
				}
				sub = sub.erase(0, pos + 1);
			}
			sub += c;
		}

		return std::max(sub.size(), sub_bk.size());
	}

	bool test(string input, int expected_length) {
		return lengthOfLongestSubstring(input) == expected_length;
	}
};

int main()
{
	Solution s;
	assert(s.test("abcabcbb", 3));
	assert(s.test("bbbbb", 1));
	assert(s.test("pwwkew", 3));
	assert(s.test("dvdf", 3));

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
