#include "../common/TreeNode.h"

/*
ִ����ʱ��0 ms, ������ C++ �ύ�л�����100.00%���û�
�ڴ����ģ�6.9 MB, ������ C++ �ύ�л�����70.87%���û�
*/
int findSecondMinimumValue(TreeNode* root) {    
    // ������Ҳ�����ġ�����ֱ��ȫ���������ҵ��ڶ�С�ľ����ˡ�����    
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