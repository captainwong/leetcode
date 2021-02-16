#include "../common/TreeNode.h"

/*
执行用时：8 ms, 在所有 C++ 提交中击败了98.80%的用户
内存消耗：21.2 MB, 在所有 C++ 提交中击败了60.88%的用户
*/
namespace sln1 {
bool isBalanced(TreeNode* node, int& h) {
    if (!node) { h = -1; return true; }
    int l = 0, r = 0;
    bool bl = isBalanced(node->left, l);
    if (!bl) { return false; }
    bool br = isBalanced(node->right, r);
    if (!br) { return false; }
    h = 1 + max(l, r);
    return (abs(l - r) < 2);
}

bool isBalanced(TreeNode* root) {
    int h = 0;
    return isBalanced(root, h);
}
}

/*
执行用时：12 ms, 在所有 C++ 提交中击败了93.84%的用户
内存消耗：20.4 MB, 在所有 C++ 提交中击败了79.56%的用户
*/
namespace sln2 {
int getDepth(TreeNode* node) {
    if (!node) { return 0; }
    return max(getDepth(node->left), getDepth(node->right)) + 1;
}

bool isBalanced(TreeNode* root) {
    if (!root) { return true; }
    return isBalanced(root->left) && isBalanced(root->right) && (abs(getDepth(root->left) - getDepth(root->right)) <= 1);
}
}


int main()
{
    //assert(isBalanced(TreeNode::construct({ 1,-1,2,-1,3 })) == false);
    //assert(isBalanced(TreeNode::construct({ 3,9,20,-1,-1,15,7 })) == true);
    assert(sln1::isBalanced(TreeNode::construct({ 1,2,2,3,-1,-1,3,4,-1,-1,4 })) == true);
    vector<int> a;
    //a.
}