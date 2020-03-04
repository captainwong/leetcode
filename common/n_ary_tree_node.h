#pragma once

#include "leetcode.h"

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }

    static Node* construct(const std::string& lcInput) {
        auto input = convertLeetcodeInputToStringVector(lcInput);
        Node* root = new Node(stoi(input[0])); assert(input[1] == "null");
        vector<Node*> level; level.push_back(root);
        for (size_t i = 2; i < input.size(); ) {
            vector<Node*> tmp;
            for (auto p : level) {
                while (i < input.size() && input[i] != "null") {
                    auto node = new Node(stoi(input[i++]));
                    p->children.push_back(node);
                    tmp.push_back(node);
                }
                if (i >= input.size()) { break; }  
                else if (input[i] == "null") { i++; }
            }
            level = tmp;
        }
        return root;
    }
};
