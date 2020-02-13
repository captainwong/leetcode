#include "../common/TreeNode.h"

int sumRight(TreeNode* node) {
    if (!node) { return 0; }

}

void convertBST(TreeNode* node, int rps) {
    if (!node) { return; }
    if (node->right) {
        convertBST(node->right, rps);
        node->val += node->right->val;
    } else {
        node->val += rps;
    }
    if (node->left) {
        convertBST(node->left, node->val);
    }
}

TreeNode* convertBST(TreeNode* root) {
    convertBST(root, 0);
    return root;
}

int main()
{
    //assert(TreeNode::equals(convertBST(TreeNode::construct({ 2,0,3,-4,1 })), { 5,6,3,2,6 }));
    assert(TreeNode::equals(convertBST(TreeNode::construct({ 1,0,4,-2,-1,3 })), { 8,8,4,6,-1,7 }));
}