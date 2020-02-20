#include "../common/TreeNode.h"

int getDepth(TreeNode* p, int d) {
    if (!p) { return d; }
    int d1 = getDepth(p->left, d + 1);
    int d2 = getDepth(p->right, d + 1);
    return max(d1, d2);
}

int getDepth2(TreeNode* p, int d) {
    if (!p)return d;
    while (p) {
        if (p->left && p->right) {
            int d1 = getDepth2(p->left, d+1);
            int d2 = getDepth2(p->right, d+1);
            return d = max(d1, d2);
        } else if (p->left) {
            p = p->left;
            d++;
        } else if (p->right) {
            p = p->right;
            d++;
        } else {
            break;
        }
    }
    return d;
}

int maxDepth(TreeNode* root) {
    if (!root) { return 0; }
    int d = 1;
    return getDepth2(root, d);
}

int main()
{
    assert(maxDepth(TreeNode::construct({ 3,9,20,-1,-1,15,7 })) == 3);
}