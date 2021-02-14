#include "../common/TreeNode.h"

/*
执行用时：32 ms, 在所有 C++ 提交中击败了47.55%的用户
内存消耗：52.4 MB, 在所有 C++ 提交中击败了33.05%的用户
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
执行用时：28 ms, 在所有 C++ 提交中击败了63.73%的用户
内存消耗：23.9 MB, 在所有 C++ 提交中击败了63.63%的用户
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