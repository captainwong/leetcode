#include <vector>
#include <string>
#include <assert.h>

using namespace std;


vector<string> findWords(vector<string> words) {
    char keys[128] = { 0 };
    for (auto c : "qwertyuiop") {
        if (c != 0) {
            keys[c] = keys[c - 32] = 1;
        }
    }
    for (auto c : "asdfghjkl") {
        if (c != 0) {
            keys[c] = keys[c - 32] = 2;
        }
    }
    for (auto c : "zxcvbnm") {
        if (c != 0) {
            keys[c] = keys[c - 32] = 3;
        }
    }

    for (auto iter = words.begin(); iter != words.end(); ) {
        int row = 0;
        for (auto c : *iter) {
            if (keys[c] != 0) {
                if (row == 0) {
                    row = keys[c];
                } else if (keys[c] != row) {
                    row = 0;
                    break;
                }
            }
        }
        if (row != 0) {
            iter++;
        } else {
            iter = words.erase(iter);
        }
    }
    return words;
}

int main()
{
    assert(findWords(vector<string>({ "Aasdfghjkl","Qwertyuiop","zZxcvbnm" })) == vector<string>({"Aasdfghjkl", "Qwertyuiop", "zZxcvbnm"}));
}