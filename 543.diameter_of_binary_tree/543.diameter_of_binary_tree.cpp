#include "../common/TreeNode.h"
#include "../common/graph.h"

int maxSide = 0;

// 计算最大单边
int maxSides(TreeNode* node) {
    if (!node) { return 0; }
    int sides = 0; int l = 0, r = 0, totalSides = 0;
    if (node->left || node->right) {
        sides++;
    }
    if (node->left) {
        totalSides++;
        l = maxSides(node->left);
    }
    if (node->right) {
        totalSides++;
        r = maxSides(node->right);
    }
    sides += max(l, r);
    totalSides += l + r;
    if (totalSides > maxSide) {
        maxSide = totalSides;
    }
    return sides;
}

int diameterOfBinaryTree(TreeNode* node) {
    if (!node) { return 0; }
    int sides = 0;
    if (node->left) {
        sides++;
        sides += maxSides(node->left);
    }
    if (node->right) {
        sides++;
        sides += maxSides(node->right);
    }
    return max(sides, maxSide);
}


int main()
{
    assert(diameterOfBinaryTree(TreeNode::construct({ 1,2,3,4,5 })) == 3);
    assert(diameterOfBinaryTree(TreeNode::construct({ 2,1,4,3,-1,5 })) == 4);
    auto node = TreeNode::construct(
        convertLeetcodeInputToStringVector(
            "[4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2]"
        )
    );
    toPng(node);

    assert(diameterOfBinaryTree(node)  == 8);
}