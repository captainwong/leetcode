#include <string>
#include <vector>
#include <list>
#include <assert.h>

using namespace std;

enum class PatternType {
    Char, // a
    CharOne, // .
    CharAny, // a*
    Any, // .*
};
struct PatternItem {
    PatternType type = PatternType::Char;
    char c = 0;
};

list<PatternItem> parsePattern(const string& p) {
    list<PatternItem> items;
    char prev = 0;
    for (size_t i = 0; i <= p.size(); i++) {
        if (i < p.size()) {
            char c = p[i];
            if (prev == 0) {
            }
            else if (prev == '.') {
                if (c == '*') {
                    items.emplace_back(PatternItem{ PatternType::Any, c });
                }
                else { 
                    items.emplace_back(PatternItem{ PatternType::CharOne, prev });
                }
            }
            else if (prev == '*') {

            }
            else { // prev == char
                if (c == '*') {
                    items.emplace_back(PatternItem{ PatternType::CharAny, prev });
                }
                else { // c == char
                    items.emplace_back(PatternItem{ PatternType::Char, prev });
                }
            }
            prev = c;
        }
        else {
            if (isalpha(prev)) {
                items.emplace_back(PatternItem{ PatternType::Char, prev });
            }
            else if (prev == '.') {
                items.emplace_back(PatternItem{ PatternType::CharOne, prev });
            }
        }
    }

    
    return items;
}



bool isMatch(string s, string p) {
    size_t pos = 0;
    auto patterns = parsePattern(p);
    list<PatternItem> outstandingPatterns;
    for (auto iter = patterns.begin(); iter != patterns.end(); ) {
        auto pattern = *iter;
        switch (pattern.type) {
        case PatternType::Char:
            if (pos == s.size() || s[pos] != pattern.c) { return false; }
            pos++;
            break;
        case PatternType::CharOne:
            pos++;
            break;
        case PatternType::CharAny:
        {
            bool nextMatched = false;
            outstandingPatterns.push_back(pattern);
            iter++;
            if (iter != patterns.end()) {
                auto nextPattern = *iter;

            }
            if (!nextMatched) {
                if (pos == s.size()) { return false; }
                for (size_t i = pos; s[pos] == pattern.c && i < s.size(); i++, pos++) {}
            }
        }
            break;
        case PatternType::Any:
            if (pos == s.size()) { return false; }
            {
                char c = s[pos++];
                for (size_t i = pos; i < s.size() && s[pos] == c; i++, pos++) {}
            }
            break;
        }
    }


    return pos == s.size();
}

int main()
{
    /*assert(isMatch("aa", "a") == false);
    assert(isMatch("aa", "a*") == true);
    assert(isMatch("aab", "c*a*b") == true);
    assert(isMatch("mississippi", "mis*is*ip*.") == true);
    assert(isMatch("aaa", "a.a") == true);
    assert(isMatch("aaa", "a*a") == true);
    assert(isMatch("ab", ".*c") == false);*/
    assert(isMatch("ab", ".*") == true);

}
