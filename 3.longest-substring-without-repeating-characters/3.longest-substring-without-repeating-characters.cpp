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

Constraints:
0 <= s.length <= 5 * 10^4
s consists of English letters, digits, symbols and spaces.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#if 1

/*
执行用时：0 ms, 在所有 C 提交中击败了100.00%的用户
内存消耗：5.6 MB, 在所有 C 提交中击败了92.25%的用户
*/


#include <stdio.h>
#include <string.h>
#include <assert.h>

char sub[50001];

int indexof(char* s, int slen, char c) {
	int pos = 0;
	char* end = s + slen;
	while (s < end && *s) {
		if (*s++ == c) {
			return pos;
		}
		pos++;
	}
	return -1;
}


int lengthOfLongestSubstring(const char* s) {
	int l1 = 0;
	int l2 = 0;
	while (*s) {
		int pos = indexof(sub, l1, *s);
		if (pos != -1) {
			if (l1 > l2) {
				l2 = l1;
			}
			memmove(sub, sub + pos + 1, l1 - pos - 1);
			l1 -= pos + 1;
		}
		sub[l1++] = *s++;
	}

	return l1 > l2 ? l1 : l2;
}

int main()
{
	assert(lengthOfLongestSubstring("abcabcbb") == 3);
	assert(lengthOfLongestSubstring("bbbbb") == 1);
	assert(lengthOfLongestSubstring("pwwkew") == 3);
	assert(lengthOfLongestSubstring("dvdf") == 3);
}

#else

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

#endif
