#include "../common/TreeNode.h"

void travel(TreeNode* p, size_t d, vector<vector<int>>& v) {
    if (!p)return;
    while (p) {
        if (p->left && p->right) {
            if (v.size() <= d) { v.emplace_back(vector<int>()); }
            v[d].push_back(p->left->val);
            v[d].push_back(p->right->val);
            travel(p->left, d + 1, v);
            travel(p->right, d + 1, v);
            return;
        } else if (p->left) {
            if (v.size() <= d) { v.emplace_back(vector<int>()); }
            v[d].push_back(p->left->val);
            p = p->left;
            d++;
        } else if (p->right) {
            if (v.size() <= d) { v.emplace_back(vector<int>()); }
            v[d].push_back(p->right->val);
            p = p->right;
            d++;
        } else {
            break;
        }
    }
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> v;
    if (!root) { return v; }
    if (v.size() < 1) { v.emplace_back(vector<int>()); }
    v[0].push_back(root->val);
    travel(root, 1, v);
    return v;
}

int main()
{
    vector<int> i = { 3,9,20,-1,-1,15,7 };
    vector<vector<int>> o = {
        {3},
        {9,20},
        {15,7},
    };
    assert(levelOrder(construct(i)) == o);
}