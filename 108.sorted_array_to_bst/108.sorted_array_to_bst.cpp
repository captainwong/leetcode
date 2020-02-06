#include "../common/TreeNode.h"

TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.empty()) { return nullptr; }
    int m = nums.size() / 2;
    TreeNode* root = new TreeNode(nums[m]);
    vector<TreeNode*> level; level.push_back(root);
    for (int i = m - 1, j = nums.size() - 1; !(i < 0 && j <= m);) {
        vector<TreeNode*> tmp;
        int numsLeft = i + 1 + j - m;
        if (numsLeft > (int)level.size()) {
            for (auto& p : level) {
                if (p) {
                    TreeNode* left = nullptr;
                    TreeNode* right = nullptr;

                    if (i >= 0) {
                        left = p->left = new TreeNode(nums[i]);
                        i--;
                    } 
                    tmp.push_back(left);
                    
                    if (j > m) {
                        right = p->right = new TreeNode(nums[j]);
                        j--;
                    }
                    tmp.push_back(right);
                }
            }
        } else {
            for (auto& p : level) {
                if (p) {
                    if (i >= 0) {
                        TreeNode* left = p->left = new TreeNode(nums[i]);
                        i--;
                        tmp.push_back(left);
                    } else if (j > m) {
                        TreeNode* left = p->left = new TreeNode(nums[j]);
                        j--;
                        tmp.push_back(left);
                    }
                }
            }
        }
        
        level = tmp;
    }
    return root;
}

int main()
{
    // -10,-3,0,5,9
    // 0,-3,9,-10,null,5


    //vector<int> i = { -10,-3,0,5,9 };
    //vector<string> o = { "0", "-3", "9", "-10", "null", "5" };  

    if (0) {
        vector<int> i = { 3,5,8 };
        vector<string> o = { "5", "3", "8" };
        auto root = sortedArrayToBST(i);
        auto s = treeToString(root);
        assert(s == o);
    }
    
    if (0) {
        vector<int> i = { -10,-3,0,5,9 };
        vector<string> o = { "0","-3","9","-10","null","5" };
        auto root = sortedArrayToBST(i);
        auto s = treeToString(root);
        assert(s == o);
    }

    if (1) {
        vector<int> i = { 0,1,2,3,4,5 };
        vector<string> o = { "3","1","5","0","2","4" };
        auto root = sortedArrayToBST(i);
        auto s = treeToString(root);
        assert(s == o);
    }
}