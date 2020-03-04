#pragma once

#include "leetcode.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    static TreeNode* find(TreeNode* root, int val) {
        if (!root) { return NULL; }
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            auto p = s.top(); s.pop();
            if (p->val == val) { return p; }
            if (p->left) { if (p->left->val == val) { return p->left; } s.push(p->left); }
            if (p->right) { if (p->right->val == val) { return p->right; } s.push(p->right); }
        }
        return NULL;
    }

    static TreeNode* construct(std::initializer_list<int> n) {
        if (n.size() == 0) { return nullptr; }
        auto i = n.begin();
        auto root = new TreeNode(*i++);
        vector<TreeNode*> level;
        level.push_back(root); 
        while (i < n.end()) {
            vector<TreeNode*> tmp;
            for (auto& p : level) {
                if (p && p->val != -1) {
                    TreeNode* left = p->left = (i >= n.end() || *i == -1) ? nullptr : new TreeNode(*i); i++;
                    TreeNode* right = p->right = (i >= n.end() || *i == -1) ? nullptr : new TreeNode(*i); i++;
                    tmp.push_back(left);
                    tmp.push_back(right);
                }
            }
            level = tmp;
        }
        return root;
    }

    static TreeNode* construct(const vector<int>& v) {
        auto root = new TreeNode(v[0]);
        vector<TreeNode*> level;
        level.push_back(root);
        for (size_t i = 1; i < v.size(); ) {
            vector<TreeNode*> tmp;
            for (auto& p : level) {
                if (p && p->val != -1) {
                    TreeNode* left = p->left = (i >= v.size() || v[i] == -1) ? nullptr : new TreeNode(v[i]); i++;
                    TreeNode* right = p->right = (i >= v.size() || v[i] == -1) ? nullptr : new TreeNode(v[i]); i++;
                    tmp.push_back(left);
                    tmp.push_back(right);
                }
            }
            level = tmp;
        }
        return root;
    }

    static TreeNode* construct(const vector<string>& v) {
        if (v.empty() || v[0] == "null") { return nullptr; }
        auto root = new TreeNode(stoi(v[0]));
        vector<TreeNode*> level;
        level.push_back(root);
        for (size_t i = 1; i < v.size(); ) {
            vector<TreeNode*> tmp;
            for (auto& p : level) {
                if (p && p->val != -1) {
                    TreeNode* left = p->left = (i >= v.size() || v[i] == "null") ? nullptr : new TreeNode(stoi(v[i])); i++;
                    TreeNode* right = p->right = (i >= v.size() || v[i] == "null") ? nullptr : new TreeNode(stoi(v[i])); i++;
                    tmp.push_back(left);
                    tmp.push_back(right);
                }
            }
            level = tmp;
        }
        return root;
    }

    //! 层次遍历，若节点为null，以"null"表示
    static vector<string> toStringVector(TreeNode* root) {
        vector<string> v;
        if (!root) { return v; }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            v.push_back(p ? to_string(p->val) : "null");
            if (!p) { continue; }
            q.push(p->left);
            q.push(p->right);
        }
        while (!v.empty() && v.back() == "null") {
            v.pop_back();
        }
        return v;
    }

    //! 层次遍历，若节点为null，以-1表示
    static vector<int> toIntVector(TreeNode* root) {
        vector<int> v;
        if (!root) { return v; }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            v.push_back(p ? (p->val) : -1);
            if (!p) { continue; }
            q.push(p->left);
            q.push(p->right);
        }
        while (!v.empty() && v.back() == -1) {
            v.pop_back();
        }
        return v;
    }

    static bool equals(TreeNode* root, const vector<string>& vs) {
        return toStringVector(root) == vs;
    }

    static bool equals(TreeNode* root, const vector<int>& vi) {
        return toIntVector(root) == vi;
    }

    static bool equals(const vector<int>& vi, const vector<string>& vs) {
        if (vi.size() != vs.size()) { return false; }
        for (size_t i = 0; i < vi.size(); i++) {
            if (vs[i] == "null") {
                if (vi[i] != -1) { return false; }
            } else {
                if (to_string(vi[i]) != vs[i]) { return false; }
            }
        }
        return true;
    }

    static bool equals(const vector<string>& vs, const vector<int>& vi) {
        return equals(vi, vs);
    }

};

