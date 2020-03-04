#include "../common/n_ary_tree_node.h"

vector<int> postorder(Node* root) {
    vector<int> r;
    if (!root) { return r; }
    stack<Node*> s; s.push(root);
    while (!s.empty()) {
        auto node = s.top();
        if (node->children.empty()) {
            r.push_back(node->val);
            s.pop();
        } else {
            for (auto iter = node->children.rbegin(); iter != node->children.rend(); iter++) {
                s.push(*iter);
            }
        }
    }
    return r;
}

int main() {
    assert(postorder(Node::construct("[1,null,3,2,4,null,5,6]")) == vector<int>({5, 6, 3, 2, 4, 1}));
}