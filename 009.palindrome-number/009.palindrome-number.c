#include <stdio.h>

/*
Given an integer x, return true if x is palindrome integer.

An integer is a palindrome when it reads the same backward as forward.

For example, 121 is a palindrome while 123 is not.
 

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 

Constraints:

-2^31 <= x <= 2^31 - 1
 

Follow up: Could you solve it without converting the integer to a string?

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/palindrome-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

typedef char bool;
#define true 1
#define false 0


/*
执行用时：16 ms, 在所有 C 提交中击败了20.22%的用户
内存消耗：5.6 MB, 在所有 C 提交中击败了96.59%的用户
*/

bool isPalindrome(int x) {
    if (x < 0) { return false; }
    int digits[11];
    int n = 0;
    while (x) {
        digits[n++] = x % 10;
        x /= 10;
    }
    for (int i = 0; i < n / 2; i++) {
        if (digits[i] != digits[n - i - 1]) {
            return false;
        }
    }
    return true;
}

int main()
{

}