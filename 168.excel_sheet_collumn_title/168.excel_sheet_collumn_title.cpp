#include <string>
#include <assert.h>

using namespace std;

string convertToTitle(int n) {
    n--;
    string r;
    int m = n % 26;
    n /= 26;
    bool last1 = n == 1;
    while (n > 1 || last1) {
        last1 = false;
        r.insert(r.begin(), ((n - 1) % 26) + 'A');
        last1 = (n>26) && (n % 26);
        n /= 26;
    }
    r.push_back(m + 'A');
    return r;
}

int main()
{
    for (char i = 1; i <= 26; i++) {
        string s;
        s.push_back('A' + i - 1);
        assert(convertToTitle(i) == s);
    }

    for (char i = 27; i <= 52; i++) {
        string s = "A"; s.push_back(i - 27 + 'A');
        assert(convertToTitle(i) == s);
    }

    for (char i = 53; i <= 78; i++) {
        string s = "B"; s.push_back(i - 53 + 'A');
        assert(convertToTitle(i) == s);
    }

    assert(convertToTitle(701) == "ZY");
    assert(convertToTitle(702) == "ZZ");
    assert(convertToTitle(703) == "AAA");
    assert(convertToTitle(1048) == "ANH");
}