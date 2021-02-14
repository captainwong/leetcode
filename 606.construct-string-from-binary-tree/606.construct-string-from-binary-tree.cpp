#include "../common/TreeNode.h"

/*
ִ����ʱ��32 ms, ������ C++ �ύ�л�����47.55%���û�
�ڴ����ģ�52.4 MB, ������ C++ �ύ�л�����33.05%���û�
*/
namespace sln1 {
string tree2str(TreeNode* t) {
    string ret;
    if (t) {
        ret += to_string(t->val);
        if (t->left && t->right) {
            ret.push_back('(');
            ret += tree2str(t->left);
            ret.push_back(')');
            ret.push_back('(');
            ret += tree2str(t->right);
            ret.push_back(')');
        } else if (t->left) {
            ret.push_back('(');
            ret += tree2str(t->left);
            ret.push_back(')');
        } else if (t->right) {
            ret.push_back('(');
            ret.push_back(')');
            ret.push_back('(');
            ret += tree2str(t->right);
            ret.push_back(')');
        } else {
            //ret += "()";
        }
    }
    return ret;
}
}


/*
ִ����ʱ��28 ms, ������ C++ �ύ�л�����63.73%���û�
�ڴ����ģ�23.9 MB, ������ C++ �ύ�л�����63.63%���û�
*/
namespace sln2 {

string tree2str(TreeNode* tree) {
    string ret;
    if (tree) {
        stack<TreeNode*> s;
        unordered_set<TreeNode*> visited;
        s.push(tree);

        while (!s.empty()) {
            auto t = s.top(); 
            if (visited.find(t) != visited.end()) {
                s.pop();
                ret.push_back(')');
            } else {
                visited.insert(t);
                ret.push_back('(');
                ret += to_string(t->val);
                if (!t->left && t->right) {
                    ret.push_back('(');
                    ret.push_back(')');
                }
                if (t->right) {
                    s.push(t->right);
                }
                if (t->left) {
                    s.push(t->left);
                }
            }
        }
        ret = ret.substr(1, ret.size() - 2);
    }
    return ret;
}

}

int main()
{

}