#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/longest-palindromic-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



#define ver 3


#if ver == 1
// 暴力计算所有子串，O(n^3)
/*
执行用时：216 ms, 在所有 C 提交中击败了28.05%的用户
内存消耗：5.8 MB, 在所有 C 提交中击败了98.30%
的用户
*/
char res[1001];

int is_pallindrome(char* s, int n) {
    if (n == 1) return 1;
    else if (n == 2) { return s[0] == s[1]; }
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1]) {
            return 0;
        }
    }
    return 1;
}

char* longestPalindrome(char* s) {
    int longest = 0;
    res[0] = '\0';
    int slen = strlen(s);
    if (slen < 2) {
        return s;
    }
    for (int i = 0; i < slen; i++) {
        for (int j = i; j < slen; j++) {
            if (j - i + 1 > longest && is_pallindrome(s + i, j - i + 1)) {
                longest = j - i + 1;
                memcpy(res, s + i, j - i + 1);
                if (longest == slen) {
                    return s;
                }
            }
        }
    }
    res[longest] = '\0';
    return res;
}

#elif ver == 2
// 中心扩散法 O(n^2)
/*
执行用时：20 ms, 在所有 C 提交中击败了60.93%的用户
内存消耗：5.9 MB, 在所有 C 提交中击败了89.44%的用户
*/

char res[1001];

char* longestPalindrome(char* s) {    
    int slen = strlen(s);
    if (slen < 2) {
        return s;
    }
    int longest = 1, longest_start = 0, len;
    res[0] = *s;
    for (int i = 1; i < slen; i++) {
        int len = 1;
        int left = i - 1, right = i + 1;
        while (left >= 0 && s[left] == s[i]) {
            len++;
            left--;
        }
        while (right < slen && s[right] == s[i]) {
            len++;
            right++;
        }
        while (left >= 0 && right < slen && s[left] == s[right]) {
            len += 2;
            left--;
            right++;
        }
        if (len > longest) {
            longest = len;
            longest_start = left + 1;
        }
    }
    memcpy(res, s + longest_start, longest);
    res[longest] = '\0';
    return res;
}

#elif ver == 3
// 动态规划，O(n^2)，不如ver2
/*
执行用时：260 ms, 在所有 C 提交中击败了18.83%的用户
内存消耗：7 MB, 在所有 C 提交中击败了21.06%的用户
*/

char res[1001];
char* longestPalindrome(char* s) {
    int slen = strlen(s);
    if (slen < 2) {
        return s;
    }
    int longest = 1, longest_start = 0;
    res[0] = *s;
    char dp[1000][1000] = { 0 };
    for (int i = 0; i < slen; i++) {
        dp[i][i] = 1;
    }

    for (int L = 2; L <= slen; L++) {
        for (int i = 0; i < slen; i++) {
            int j = L + i - 1;
            if (j >= slen) {
                break;
            }
            if (s[i] != s[j]) {
                dp[i][j] = 0;
            } else {
                if (j - i < 3) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }

            if (dp[i][j] && L > longest) {
                longest = L;
                longest_start = i;
            }
        }
    }

    memcpy(res, s + longest_start, longest);
    res[longest] = '\0';
    return res;
}



#endif

int main()
{
	char* res = longestPalindrome("babad");

}
