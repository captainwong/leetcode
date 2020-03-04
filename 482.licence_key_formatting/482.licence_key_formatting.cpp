#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;


string licenseKeyFormatting(string S, int K) {
    reverse(S.begin(), S.end());
    int i = 0;
    for (auto iter = S.rbegin(); iter != S.rend(); ) {
        while (iter != S.rend() && *iter == '-') {
            iter = S.reriter);
        }
        if (iter == S.end()) { break; }
        *iter = toupper(*iter);
        if (++i == K && (iter + 1 != S.end())) {
            i = 0;
            if (*++iter != '-') {
                iter = S.insert(iter, '-');
            }
        }
        iter++;
    }
    reverse(S.begin(), S.end());
    for (auto iter = S.begin(); iter != S.end(); ) {
        if (*iter == '-') {
            iter = S.erase(iter);
        } else {
            break;
        }
    }
    return S;
}

int main()
{
    assert(licenseKeyFormatting("--a-a-a-a--", 2) == "AA-AA");
    assert(licenseKeyFormatting("0123456789", 1) == "0-1-2-3-4-5-6-7-8-9");
}