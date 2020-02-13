#include <assert.h>
#include <string>

using namespace std;

string reverseStr(string s, int k) {
    if (k < 2) { return s; }
    int n = s.size() / 2 / k;
    for (int i = 0; i < n; i++) {
        int l = i * 2 * k;
        int r = i * 2 * k + k - 1;
        while (l < r) {
            swap(s[l++], s[r--]);
        }
    }
    int n2 = s.size() - n * 2 * k;
    if (n2 < k) {
        int l = s.size() - n2;
        int r = s.size() - 1;
        while (l < r) {
            swap(s[l++], s[r--]);
        }
    } else {
        int l = s.size() - n2;
        int r = l + k - 1;
        while (l < r) {
            swap(s[l++], s[r--]);
        }
    }
    return s;
}

int main()
{
    assert(reverseStr("abcdefg", 2) == "bacdfeg");
}