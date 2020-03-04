#include "../common/TreeNode.h"


/*
ִ����ʱ :52 ms, ������ C++ �ύ�л�����19.82%���û�
�ڴ����� :30.9 MB, ������ C++ �ύ�л�����5.10%���û�
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
ִ����ʱ :32 ms, ������ C++ �ύ�л�����78.13%���û�
�ڴ����� :30.1 MB, ������ C++ �ύ�л�����5.10%���û�
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