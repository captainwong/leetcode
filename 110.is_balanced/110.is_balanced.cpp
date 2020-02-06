#include "../common/TreeNode.h"

int getDepth2(TreeNode* p, int d) {
    if (!p)return d;
    d++;
    while (p) {
        if (p->left && p->right) {
            int d1 = getDepth2(p->left, d);
            int d2 = getDepth2(p->right, d);
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

bool isBalanced(TreeNode* root) {
    if (!root) { return true; }
    int d1 = getDepth2(root->left, 0);
    int d2 = getDepth2(root->right, 0);
    return abs(d1 - d2) < 2;
}

int main()
{
    //assert(isBalanced(construct({ 1,-1,2,-1,3 })) == false);
    assert(isBalanced(construct({ 3,9,20,-1,-1,15,7 })) == true);
}