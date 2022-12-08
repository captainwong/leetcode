#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define cpp 0

#if cpp

/*
执行用时：12 ms, 在所有 C++ 提交中击败了48.25%的用户
内存消耗：10.4 MB, 在所有 C++ 提交中击败了48.76%的用户
*/

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) { return s; }
        vector<string> lines(numRows);
        bool down = true;
        size_t line = 0;
        for (size_t i = 0; i < s.size(); i++) {
            lines[line].push_back(s[i]);
            if (down) {
                line++;
            } else {
                line--;
            }
            if (line == numRows - 1 || line == 0) {
                down = !down;
            }
        }
        string ret;
        for (auto i : lines) {
            ret += i;
        }
        return ret;
    }
};

#else

#define ver 4

#if ver == 1
/*
执行用时：12 ms, 在所有 C 提交中击败了55.54%的用户
内存消耗：35.8 MB, 在所有 C 提交中击败了7.68%的用户
*/
char res[1001];
typedef struct Str {
    char* s;
    int len;
}Str;

char* convert(char* s, int numRows) {
    if (numRows < 2) { return s; }
    int slen = strlen(s);
    Str* lines = (Str*)malloc(sizeof(Str) * numRows);
    for (int i = 0; i < numRows; i++) {
        lines[i].s = (char*)malloc(sizeof(char) * slen);
        memset(lines[i].s, ' ', sizeof(char) * slen);
        lines[i].s[slen - 1] = '\0';
        lines[i].len = 0;
    }

    for (int line = 0, down = 1; *s;) {
        lines[line].s[lines[line].len++] = *s++;
        if (down) {
            line++;
        } else {
            line--;
        }
        if (line == 0 || line == numRows - 1) {
            down = !down;
        }
    }

    slen = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(res + slen, lines[i].s, lines[i].len);
        slen += lines[i].len;
    }
    res[slen] = '\0';
    return res;
}
#elif ver == 2

/*
执行用时：4 ms, 在所有 C 提交中击败了87.31%的用户
内存消耗：6.9 MB, 在所有 C 提交中击败了52.71%的用户
*/

char res[1001];
typedef struct Str {
    char s[1001];
    int len;
}Str;

Str lines[1000];

char* convert(char* s, int numRows) {
    if (numRows < 2) { return s; }
    int slen = strlen(s);
    for (int i = 0; i < numRows; i++) {
        lines[i].len = 0;
    }

    for (int line = 0, down = 1; *s;) {        
        lines[line].s[lines[line].len++] = *s++;
        if (down) {
            line++;
        } else {
            line--;
        }
        if (line == 0 || line == numRows - 1) {
            down = !down;
        }
    }

    slen = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(res + slen, lines[i].s, lines[i].len);
        slen += lines[i].len;
    }
    res[slen] = '\0';
    return res;
}

#elif ver==3

// 官方题解方法二：压缩矩阵空间
/*
t = r + r - 2 = 2r - 2
半周期 t/2 = r-1
每个周期占用矩阵的 1 + r - 2 = r - 1 列
*/

/*
执行用时：8 ms, 在所有 C 提交中击败了65.01%的用户
内存消耗：7.1 MB, 在所有 C 提交中击败了49.01%的用户
*/


char res[1001];
typedef struct Str {
    char s[1001];
    int len;
}Str;

Str lines[1000];

char* convert(char* s, int numRows) {
    int slen = strlen(s);
    if (numRows < 2 || numRows >= slen) return s;
    for (int i = 0; i < numRows; i++) {
        lines[i].len = 0;
    }

    for (int i = 0, line = 0, t = numRows * 2 - 2; i < slen; i++) {
        lines[line].s[lines[line].len++] = s[i];
        i % t < numRows - 1 ? ++line : --line; // i%t < 半周期=r-1 则向下，否则向右上
    }
    slen = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(res + slen, lines[i].s, lines[i].len);
        slen += lines[i].len;
    }
    res[slen] = '\0';
    return res;
}

#elif ver == 4
// 官方题解 方法3 直接构造

char* convert(char* s, int numRows) {

}

#endif
int main()
{
    assert(strcmp(convert((char*)"PAYPALISHIRING", 3), "PAHNAPLSIIGYIR") == 0);
    assert(strcmp(convert((char*)"ABCD", 2), "ACBD") == 0);
    assert(strcmp(convert((char*)"AB", 1), "AB") == 0);
    
}
#endif