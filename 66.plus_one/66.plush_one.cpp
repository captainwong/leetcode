#include <vector>

using namespace std;

vector<int> plusOne(vector<int>& digits) {
    int carry = 1;
    for (auto iter = digits.rbegin(); iter != digits.rend(); iter++) {
        auto& val = *iter;
        val += carry;
        carry = 0;
        if (val >= 10) {
            val -= 10;
            carry = 1;
        }
    }
    if (carry) {
        digits.insert(digits.begin(), carry);
    }
    return digits;
}

int main()
{

}