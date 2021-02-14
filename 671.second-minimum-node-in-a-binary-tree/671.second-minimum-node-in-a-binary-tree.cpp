#include "../common/TreeNode.h"

/*
执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
内存消耗：6.9 MB, 在所有 C++ 提交中击败了70.87%的用户
*/
int findSecondMinimumValue(TreeNode* root) {    
    // 暴力解也不慢的。。。直接全部遍历，找到第二小的就是了。。。    
    if (!root) { return -1; }
    int m = root->val;
    int n = -1;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        auto t = s.top(); s.pop();
        if (t->val > m) {
            if (n == -1 || n > t->val) {
                n = t->val;
            }
        }
        if (t->right) {
            s.push(t->right);
        }
        if (t->left) {
            s.push(t->left);
        }
    }

    return n;
}

int main()
{

}