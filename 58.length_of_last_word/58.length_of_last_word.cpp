#include <string>
#include <stdio.h>
#include <assert.h>

using namespace std;

int lengthOfLastWord(string s) {
    int len = 0;
    bool firstAlpha = false;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (isalpha(s[i])) {
            len++;
            firstAlpha = true;
        }
        else if (firstAlpha) {
            break;
        }
    }
    return len;
}

int main()
{
    assert(lengthOfLastWord("a") == 1);
    assert(lengthOfLastWord("a ") == 1);
}