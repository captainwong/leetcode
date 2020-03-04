#include "../common/TreeNode.h"


/*
执行用时 :40 ms, 在所有 C++ 提交中击败了42.40%的用户
内存消耗 :32.8 MB, 在所有 C++ 提交中击败了5.13%的用户
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
执行用时 :36 ms, 在所有 C++ 提交中击败了59.80%的用户
内存消耗 :31.6 MB, 在所有 C++ 提交中击败了5.13%的用户
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