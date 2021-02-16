#include "../common/TreeNode.h"

/*
执行用时：4 ms, 在所有 C++ 提交中击败了69.46%的用户
内存消耗：9.5 MB, 在所有 C++ 提交中击败了80.25%的用户
*/
namespace sln1 {
int minDiffInBST(TreeNode* root) {
    if (!root) { return 0; }
    queue<TreeNode*> q; q.push(root);
    vector<int> v;
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        v.push_back(p->val);
        if (p->left) { q.push(p->left); }
        if (p->right) { q.push(p->right); }
    }
    if (v.size() < 2) { return 0; }
    sort(v.begin(), v.end());
    int diff = v[1] - v[0];
    for (size_t i = 2; i < v.size(); i++) {
        diff = min(diff, v[i] - v[i - 1]);
    }
    return diff;
}
}

/*
执行用时：4 ms, 在所有 C++ 提交中击败了69.46%的用户
内存消耗：9.5 MB, 在所有 C++ 提交中击败了80.25%的用户
*/
namespace sln2 {
int minDiffInBST(TreeNode* root) {
    if (!root) { return 0; }
    stack<TreeNode*> s;
    TreeNode* t = root;
    TreeNode* prev = nullptr;
    int d = 0;
    while (true) {
        if (t) {
            s.push(t);
            t = t->left;
        } else if (!s.empty()) {
            t = s.top(); s.pop();
            if (prev) {
                if (d == 0 || t->val - prev->val < d) {
                    d = t->val - prev->val;
                    if (d == 1) { return 1; }
                }
            }
            prev = t;
            t = t->right;
        } else { break; }
    }
    return d;
}
}

int main()
{

}
