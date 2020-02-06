#include <queue>
#include <stack>
#include <assert.h>
#include <list>
#include <string>

using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* construct(const vector<int>& v) {
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

TreeNode* construct(const vector<string>& v) {
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
vector<string> treeToString(TreeNode* root) {
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
vector<int> treeToInt(TreeNode* root) {
    vector<int> v;
    if (!root) { return v; }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        v.push_back(p ? (p->val) : -1);
        if (!p) { continue; }
        if (p->left) { q.push(p->left); }
        if (p->right) { q.push(p->right); }
    }
    while (!v.empty() && v.back() == -1) {
        v.pop_back();
    }
    return v;
}

bool equals(TreeNode* root, const vector<string>& vs) {
    return treeToString(root) == vs;
}

bool equals(TreeNode* root, const vector<int>& vi) {
    return treeToInt(root) == vi;
}

bool equals(const vector<int>& vi, const vector<string>& vs) {
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

bool equals(const vector<string>& vs, const vector<int>& vi) {
    return equals(vi, vs);
}
