#include <string>
#include <assert.h>
#include <unordered_map>

using namespace std;

bool wordPattern(string pattern, string str) {
    unordered_map<char, string> p;
    unordered_map<string, char> rp;
    string word;
    size_t pos = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        bool wordFinished = false;
        if (c == ' ') {
            wordFinished = true;
        } else if (i == str.size() - 1) {
            word.push_back(c);
            wordFinished = true;
        } else {
            word.push_back(c);
        }

        if (wordFinished) {
            auto s = p[pattern[pos]];
            if (s.empty()) {
                if (rp.find(word) != rp.end()) { return false; }
                p[pattern[pos]] = word;
                rp[word] = pattern[pos++];
            } else if (s == word) {
                pos++;
            } else {
                return false;
            }
            word.clear();
        }
    }
    return pos == pattern.size();
}

int main()
{
    //assert(wordPattern("abba", "dog cat cat dog") == true);
    assert(wordPattern("abba", "dog dog dog dog") == false);
}