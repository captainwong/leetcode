#include "../common/TreeNode.h"


/*
ִ����ʱ :40 ms, ������ C++ �ύ�л�����42.40%���û�
�ڴ����� :32.8 MB, ������ C++ �ύ�л�����5.13%���û�
*/
namespace solution1 {
string toString(TreeNode* t) {
    stack<TreeNode*> s;
    s.push(t);
    string str;
    while (!s.empty()) {
        auto p = s.top(); s.pop();
        str += "#" + to_string(p->val);
        if (p->right) {
            s.push(p->right);
        }
        if (p->left) {
            s.push(p->left);
        } else {
            str += "l";
        }
        if (!p->right) {
            str += "r";
        }
    }
    return str;
}

bool isSubtree(TreeNode* s, TreeNode* t) {
    return toString(s).find(toString(t)) != string::npos;
}
}


/*
ִ����ʱ :36 ms, ������ C++ �ύ�л�����59.80%���û�
�ڴ����� :31.6 MB, ������ C++ �ύ�л�����5.13%���û�
*/
namespace solution2 {

bool isIdentical(TreeNode* s, TreeNode* t) {
    if (!s && !t) { return true; }
    else if (!s || !t) { return false; }
    else { return s->val == t->val && isIdentical(s->left, t->left) && isIdentical(s->right, t->right); }
}

bool isSubtree(TreeNode* s, TreeNode* t) {
    return isIdentical(s, t) || (s && (isSubtree(s->left, t) || isSubtree(s->right, t)));
}

}

int main()
{
    assert(solution1::isSubtree(TreeNode::construct({ 3, 4, 5, 1, 2 }),
                                TreeNode::construct({ 4, 1, 2 })));
    assert(solution2::isSubtree(TreeNode::construct({ 3, 4, 5, 1, 2 }),
                                TreeNode::construct({ 4, 1, 2 })));

    assert(solution2::isSubtree(TreeNode::construct(convertLeetcodeInputToStringVector("[1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,null,1,2]")),
                                TreeNode::construct(convertLeetcodeInputToStringVector("[1,null,1,null,1,null,1,null,1,null,1,2]"))));
}