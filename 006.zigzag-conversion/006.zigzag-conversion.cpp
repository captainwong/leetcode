#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define cpp 0

#if cpp

/*
ִ����ʱ��12 ms, ������ C++ �ύ�л�����48.25%���û�
�ڴ����ģ�10.4 MB, ������ C++ �ύ�л�����48.76%���û�
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
ִ����ʱ��12 ms, ������ C �ύ�л�����55.54%���û�
�ڴ����ģ�35.8 MB, ������ C �ύ�л�����7.68%���û�
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
ִ����ʱ��4 ms, ������ C �ύ�л�����87.31%���û�
�ڴ����ģ�6.9 MB, ������ C �ύ�л�����52.71%���û�
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

// �ٷ���ⷽ������ѹ������ռ�
/*
t = r + r - 2 = 2r - 2
������ t/2 = r-1
ÿ������ռ�þ���� 1 + r - 2 = r - 1 ��
*/

/*
ִ����ʱ��8 ms, ������ C �ύ�л�����65.01%���û�
�ڴ����ģ�7.1 MB, ������ C �ύ�л�����49.01%���û�
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
        i % t < numRows - 1 ? ++line : --line; // i%t < ������=r-1 �����£�����������
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
// �ٷ���� ����3 ֱ�ӹ���

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