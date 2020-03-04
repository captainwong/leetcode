#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
ִ����ʱ :24 ms, ������ C++ �ύ�л�����93.70%���û�
�ڴ����� :11.6 MB, ������ C++ �ύ�л�����80.06%���û�
*/
namespace my {
string::size_type findFirst(const string& s, char c, string::size_type start) {
    while (start <= s.size() / 2) { // s�������ظ��Ӵ���������2���Ӵ������һ���ַ����ظ���λ�����Ϊs.size() / 2
        if (s[start] == c && (s.size() % start == 0)) { return start; } // s.size() % start ����Ϊ0�������������Ӵ�
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
ִ����ʱ :44 ms, ������ C++ �ύ�л�����27.85%���û�
�ڴ����� :14.1 MB, ������ C++ �ύ�л�����58.96%���û�
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