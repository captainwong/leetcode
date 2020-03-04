#include "../common/TreeNode.h"


/*
执行用时 :52 ms, 在所有 C++ 提交中击败了19.82%的用户
内存消耗 :30.9 MB, 在所有 C++ 提交中击败了5.10%的用户
*/
namespace solution1 {
TreeNode* convertBST(TreeNode* root) {
    if (!root) { return root; }
    vector<TreeNode*> v;
    stack<TreeNode*> s;
    auto p = root;
    while (true) {
        if (p) { s.push(p); p = p->left; } 
        else if (!s.empty()) { p = s.top(); s.pop(); v.push_back(p); p = p->right; }
        else { break; }
    }
    if (v.size() < 2) { return root; }
    auto back = v.back();
    for (size_t i = v.size() - 2; i > 0; i--) {
        v[i]->val += back->val;
        back = v[i];
    }
    v.front()->val += back->val;
    return root;
}
}


/*
执行用时 :32 ms, 在所有 C++ 提交中击败了78.13%的用户
内存消耗 :30.1 MB, 在所有 C++ 提交中击败了5.10%的用户
*/
namespace solution2 {
TreeNode* convertBST(TreeNode* root) {
    if (!root) { return root; }
    stack<TreeNode*> s;
    auto p = root;
    int n = 0;
    while (true) {
        if (p) { s.push(p); p = p->right; } 
        else if (!s.empty()) { p = s.top(); s.pop(); p->val += n; n = p->val; p = p->left; }
        else { break; }
    }
    return root;
}
}


int main()
{
    assert(TreeNode::equals(solution1::convertBST(TreeNode::construct({ 5, 2, 13 })), { 18, 20, 13 }));
    assert(TreeNode::equals(solution1::convertBST(TreeNode::construct({ 2,0,3,-4,1 })), { 5,6,3,2,6 }));
    assert(TreeNode::equals(solution1::convertBST(TreeNode::construct({ 1,0,4,-2,-1,3 })), { 8,8,4,6,-1,7 }));

    assert(TreeNode::equals(solution2::convertBST(TreeNode::construct({ 5, 2, 13 })), { 18, 20, 13 }));
    assert(TreeNode::equals(solution2::convertBST(TreeNode::construct({ 2,0,3,-4,1 })), { 5,6,3,2,6 }));
    assert(TreeNode::equals(solution2::convertBST(TreeNode::construct({ 1,0,4,-2,-1,3 })), { 8,8,4,6,-1,7 }));

}