#include "../common/TreeNode.h"

int n = 0;
vector<int> sums = {};

int getDepth(TreeNode* node) {
    if (!node) { return 0; }
    return max(getDepth(node->left), getDepth(node->right)) + 1;
}

void trav(TreeNode* node, int level, int sum) {
    if (!node) { return; }
    sums[level] = sums[level - 1] + node->val;
    for (int i = 0; i < level; i++) {
        if (sums[level] - sums[i] == sum) { n++; }
    }
    trav(node->left, level + 1, sum);
    trav(node->right, level + 1, sum);
}

int pathSum(TreeNode* root, int sum) {
    sums.resize(getDepth(root) + 1); sums[0] = 0;
    trav(root, 1, sum);
    return n;
}


int main()
{
    assert(pathSum(TreeNode::construct(convertLeetcodeInputToStringVector("[10,5,-3,3,2,null,11,3,-2,null,1]")), 8) == 3);
}

