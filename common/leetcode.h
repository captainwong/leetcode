#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

using namespace std;

    
static const auto __fastIO = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

// in: "[4,null,-1]"
// out: ["4", "null", "-1"]
static vector<string> convertLeetcodeInputToStringVector(const std::string& input) {
    vector<string> v;
    string word;
    word.push_back(input[1]);
    for (size_t i = 2; i < input.size(); i++) {
        char c = input[i];
        if (c == ',' || c == ']') {
            v.push_back(word);
            word.clear();
        } else {
            word.push_back(c);
        }
    }
    return v;
}

// in: "[-2,0,3,-5,2,-1]"
// out: [-2,0,3,-5,2,-1]
static vector<int> convertLeetcodeInputToIntVector(const std::string& input) {
    vector<int> v;
    string word;
    word.push_back(input[1]);
    for (size_t i = 2; i < input.size(); i++) {
        char c = input[i];
        if (c == ',' || c == ']') {
            v.push_back(stoi(word));
            word.clear();
        } else {
            word.push_back(c);
        }
    }
    return v;
}
