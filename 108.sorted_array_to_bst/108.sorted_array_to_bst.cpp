#include "../common/TreeNode.h"

TreeNode* construct(vector<int>& nums, int l, int r) {
    if (l >= r) { return nullptr; }
    int m = l + (r - l) / 2;
    auto node = new TreeNode(nums[m]);
    node->left = construct(nums, l, m);
    node->right = construct(nums, m + 1, r);
    return node;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return construct(nums, 0, nums.size());
}

int main()
{
    // -10,-3,0,5,9
    // 0,-3,9,-10,null,5


    //vector<int> i = { -10,-3,0,5,9 };
    //vector<string> o = { "0", "-3", "9", "-10", "null", "5" };  

    if (1) {
        vector<int> i = { 3,5,8 };
        vector<string> o = { "5", "3", "8" };
        auto root = sortedArrayToBST(i);
        auto s = TreeNode::toStringVector(root);
        assert(s == o);
    }
    
    if (1) {
        vector<int> i = { -10,-3,0,5,9 };
        vector<string> o = { "0","-3","9","-10","null","5" };
        auto root = sortedArrayToBST(i);
        auto s = TreeNode::toStringVector(root);
        assert(s == o);
    }

    if (1) {
        vector<int> i = { 0,1,2,3,4,5 };
        vector<string> o = { "3","1","5","0","2","4" };
        auto root = sortedArrayToBST(i);
        auto s = TreeNode::toStringVector(root);
        assert(s == o);
    }
}