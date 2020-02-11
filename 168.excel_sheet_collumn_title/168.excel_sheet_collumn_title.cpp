#include <string>
#include <assert.h>

using namespace std;

string convertToTitle(int n) {
    string s;
    int m = n % 27;
    bool carried = false;
    
    if (n > 26) {
        n -= 26;
        while (n) {
            carried = true;
            s.insert(s.begin(), n - 1 + 'A');
            n /= 26;
        }
    }
    if (carried) {
        s.push_back(m + 'A');
    } else {
        s.push_back(m - 1 + 'A');
    }

    return s;
}

string convertToTitle2(int n) {
    string s;
    while (n) {
        int d = n / 26;
        int m = n % 26;
        if (m == 0) {
            if (d) {
                d--; m = 26;
            } else {
                m++;
            }
        }

        if (m) {
            s.push_back(m - 1 + 'A');
        }
        if (d) {
            s.push_back(d - 1 + 'A');
        }
        if (d <= 26) { break; }
        n = d;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    for (char i = 1; i <= 26; i++) {
        string s;
        s.push_back('A' + i - 1);
        assert(convertToTitle2(i) == s);
    }

    for (char i = 27; i <= 52; i++) {
        string s = "A"; s.push_back(i - 27 + 'A');
        assert(convertToTitle2(i) == s);
    }

    for (char i = 53; i <= 78; i++) {
        string s = "B"; s.push_back(i - 53 + 'A');
        assert(convertToTitle2(i) == s);
    }

    assert(convertToTitle2(701) == "ZY");
    assert(convertToTitle2(702) == "ZZ");
}