#include "../common/TreeNode.h"

int n = 0;

void pathSum(TreeNode* node, list<int> v, int sum, int Sum) {
    if (!node) { return; }

    while (sum + node->val > Sum && !v.empty() && v.front() > 0) {
        sum -= v.front();
        v.pop_front();
    }

    while (sum + node->val < Sum && !v.empty() && v.front() < 0) {
        sum -= v.front();
        v.pop_front();
    }

    sum += node->val;
    if (sum == Sum) {
        n++;
    }

    v.push_back(node->val);
    pathSum(node->left, v, sum, Sum);
    pathSum(node->right, v, sum, Sum);

}

int pathSum(TreeNode* root, int sum) {
    if (!root) {
        return 0;
    }
    list<int> v;
    v.push_back(root->val);
    pathSum(root->left, v, root->val, sum);
    pathSum(root->right, v, root->val, sum);
    return n;
}


int main()
{
    assert(pathSum(TreeNode::construct(convertLeetcodeInputToStringVector("[10,5,-3,3,2,null,11,3,-2,null,1]")), 8) == 3);
}

