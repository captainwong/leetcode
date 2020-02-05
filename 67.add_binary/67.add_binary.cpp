#include <string>
#include <stdio.h>
#include <assert.h>
#include <algorithm>

using namespace std;

char add(char op1, char op2, bool& carry) {
    op1 -= '0'; op2 -= '0';
    char r = op1 + op2;
    if (carry) {
        if (r == 0) {
            r = '1';
            carry = false;
        }
        else if (r == 1) {
            r = '0';
        }
        else {
            r = '1';
        }
    }
    else {
        if (r == 0) {
            r = '0';
        }
        else if (r == 1) {
            r = '1';
        }
        else {
            r = '0';
            carry = true;
        }
    }
    return r;
}

string addBinary(string a, string b) {
    string r;
    bool carry = false;
    for (size_t i = 0; i < max(a.size(), b.size()); i++) {
        char op1 = '0', op2 = '0';
        if (i < a.size()) {
            op1 = a[a.size() - i - 1];
        }
        if (i < b.size()) {
            op2 = b[b.size() - i - 1];
        }

        r.insert(r.begin(), add(op1, op2, carry));
    }
    if (carry) {
        r.insert(r.begin(), '1');
    }
    return r;
}

int main()
{
    assert(addBinary("11", "1") == "100");
}