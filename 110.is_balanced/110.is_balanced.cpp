#include "../common/TreeNode.h"

/*
ִ����ʱ��8 ms, ������ C++ �ύ�л�����98.80%���û�
�ڴ����ģ�21.2 MB, ������ C++ �ύ�л�����60.88%���û�
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
ִ����ʱ��12 ms, ������ C++ �ύ�л�����93.84%���û�
�ڴ����ģ�20.4 MB, ������ C++ �ύ�л�����79.56%���û�
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