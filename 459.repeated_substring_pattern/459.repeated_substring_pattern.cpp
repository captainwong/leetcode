#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
执行用时 :24 ms, 在所有 C++ 提交中击败了93.70%的用户
内存消耗 :11.6 MB, 在所有 C++ 提交中击败了80.06%的用户
*/
namespace my {
string::size_type findFirst(const string& s, char c, string::size_type start) {
    while (start <= s.size() / 2) { // s若包含重复子串，最少有2个子串，则第一个字符的重复的位置最大为s.size() / 2
        if (s[start] == c && (s.size() % start == 0)) { return start; } // s.size() % start 必须为0才能有整数个子串
        start++;
    }
    return string::npos;
}

bool canRepeat(const string& s, string::size_type subLen) {
    for (string::size_type i = 1; i < s.size() / subLen; i++) {        
        for (string::size_type j = subLen * i, k = 0; j < subLen * (i + 1); ) {
            if (s[j++] != s[k++]) { return false; }
        }
    }
    return true;
}

bool repeatedSubstringPattern(string s) {
    if (s.empty()) { return false; }
    size_t subLen = findFirst(s, s[0], 1);
    while (subLen != string::npos) {
        if (canRepeat(s, subLen)) { return true; }
        subLen = findFirst(s, s[0], subLen + 1);
    }
    return false;
}
}


/*
执行用时 :44 ms, 在所有 C++ 提交中击败了27.85%的用户
内存消耗 :14.1 MB, 在所有 C++ 提交中击败了58.96%的用户
*/
namespace da_li_wang {
bool repeatedSubstringPattern(string s) {
    return (s + s).find(s, 1) != s.size();
}
}

//namespace da_li_wang_pro {
//bool repeatedSubstringPattern(string s) {
//    for (size_t i = 1; i < s.size() * 2; i++) {
//
//    }
//}
//}

int main() {
    assert(my::repeatedSubstringPattern("abab") == true);
    assert(my::repeatedSubstringPattern("aabaaba") == false);
    
    assert(da_li_wang::repeatedSubstringPattern("abab") == true);
    assert(da_li_wang::repeatedSubstringPattern("aabaaba") == false);

    string s;
}