#include "../common/TreeNode.h"


/*
ִ����ʱ :28 ms, ������ C++ �ύ�л�����39.72%���û�
�ڴ����� :17.6 MB, ������ C++ �ύ�л�����23.70%���û�
*/
namespace solution1 {

struct NodeEx {
    NodeEx* parent = NULL;
    TreeNode* p = NULL;
    int d = 0;
    NodeEx(TreeNode* p, NodeEx* pp = NULL, int d = 0) : p(p), parent(pp), d(d) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) { return NULL; }
    NodeEx* np = NULL, * nq = NULL;
    auto nr = new NodeEx(root);
    nr->parent = nr;
    stack<NodeEx*> s;
    s.push(nr);
    while (!s.empty()) {
        auto cur = s.top(); s.pop();
        if (!np && cur->p->val == p->val) {
            np = new NodeEx(cur->p, cur);
        }
        if (!nq && cur->p->val == q->val) {
            nq = new NodeEx(cur->p, cur);
        }
        if (np && nq) { break; }
        if (cur->p->left) {
            if (!np && cur->p->left->val == p->val) {
                np = new NodeEx(cur->p->left, cur, cur->d + 1);
                s.push(np);
            } else if (!nq && cur->p->left->val == q->val) {
                nq = new NodeEx(cur->p->left, cur, cur->d + 1);
                s.push(nq);
            } else {
                auto n = new NodeEx(cur->p->left, cur, cur->d + 1);
                s.push(n);
            }
        }
        if (cur->p->right) {
            if (!np && cur->p->right->val == p->val) {
                np = new NodeEx(cur->p->right, cur, cur->d + 1);
                s.push(np);
            } else if (!nq && cur->p->right->val == q->val) {
                nq = new NodeEx(cur->p->right, cur, cur->d + 1);
                s.push(nq);
            } else {
                auto n = new NodeEx(cur->p->right, cur, cur->d + 1);
                s.push(n);
            }
        }
        if (np && nq) { break; }
    }
    while (np->d > nq->d) {
        np = np->parent;
    }
    while (np->d < nq->d) {
        nq = nq->parent;
    }
    while (np->p != nq->p) {
        np = np->parent;
        nq = nq->parent;
    }
    return np->p;
}
}


/*
ִ����ʱ :40 ms, ������ C++ �ύ�л�����14.66%���û�
�ڴ����� :19.9 MB, ������ C++ �ύ�л�����16.40%���û�
*/
namespace solution2 {

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) { return NULL; }
    stack<TreeNode*> s;
    s.push(root);
    unordered_map<TreeNode*, TreeNode*> parent;
    parent[root] = NULL;
    while (!s.empty()) {
        auto node = s.top(); s.pop();
        if (node->left) {
            parent[node->left] = node;
            s.push(node->left);
        }
        if (node->right) {
            parent[node->right] = node;
            s.push(node->right);
        }
    }
    unordered_set<TreeNode*> ancestor;
    while (p) {
        ancestor.insert(p);
        p = parent[p];
    }
    while (ancestor.find(q) == ancestor.end()) {
        q = parent[q];
    }
    return q;
}

}

/*
ִ����ʱ :16 ms, ������ C++ �ύ�л�����95.93%���û�
�ڴ����� :17 MB, ������ C++ �ύ�л�����29.02%���û�
*/
namespace solution3 {

TreeNode* ans = NULL;

bool traverse(TreeNode* node, TreeNode* p, TreeNode* q) {
    if (!node) { return false; }
    int m = node->val == p->val || node->val == q->val;
    int l = traverse(node->left, p, q) ? 1 : 0;
    int r = traverse(node->right, p, q) ? 1 : 0;
    if (m + l + r > 1) { ans = node; }
    return (m + l + r) > 0;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    traverse(root, p, q);
    return ans;
}

}


/*
ִ����ʱ :24 ms, ������ C++ �ύ�л�����61.96%���û�
�ڴ����� :17.7 MB, ������ C++ �ύ�л�����23.64%���û�
*/
namespace solution4 {

enum State {
    BOTH_PENDING = 2,
    LEFT_DONE = 1,
    BOTH_DONE = 0,
};

State next(State s) {
    switch (s) {
    case solution4::BOTH_PENDING: return LEFT_DONE;
    case solution4::LEFT_DONE:  return BOTH_DONE;
    default:assert(0); return BOTH_DONE;
    }
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) { return NULL; }
    stack<pair<TreeNode*, State>> s;
    s.push(make_pair(root, BOTH_PENDING));
    TreeNode* lca = NULL;
    bool one_node_found = false;
    while (!s.empty()) {
        auto pair = s.top();
        auto node = pair.first;
        TreeNode* child = NULL;
        if (pair.second != BOTH_DONE) {
            if (pair.second == BOTH_PENDING) {
                if (node == p || node == q) {
                    if (one_node_found) {
                        return lca;
                    } else {
                        one_node_found = true;
                        lca = node;
                    }
                }
                child = node->left;
            } else {
                child = node->right;
            }
            s.pop();
            pair.second = next(pair.second);
            s.push(pair);
            if (child) {
                s.push(make_pair(child, BOTH_PENDING));
            }
        } else {
            s.pop();
            if (lca == node && one_node_found) {
                lca = s.top().first;
            }
        }
    }
    return NULL;
}

}

namespace best {

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ancestor = root;
    while (true) {
        if (p->val < ancestor->val && q->val < ancestor->val) {
            ancestor = ancestor->left;
        } else if (p->val > ancestor->val && q->val > ancestor->val) {
            ancestor = ancestor->right;
        } else {
            break;
        }
    }
    return ancestor;
}

}

int main()
{
    {
        auto root = TreeNode::construct(convertLeetcodeInputToStringVector("[6,2,8,0,4,7,9,null,null,3,5]"));
        auto p = TreeNode::find(root, 2);
        auto q = TreeNode::find(root, 4);
        assert(solution1::lowestCommonAncestor(root, p, q)->val == 2);
        assert(solution2::lowestCommonAncestor(root, p, q)->val == 2);
        assert(solution3::lowestCommonAncestor(root, p, q)->val == 2); // best
        assert(solution4::lowestCommonAncestor(root, p, q)->val == 2);

    }

    {
        auto root = TreeNode::construct(convertLeetcodeInputToStringVector("[1,2,3,null,4]"));
        auto p = TreeNode::find(root, 4);
        auto q = TreeNode::find(root, 3);
        assert(solution1::lowestCommonAncestor(root, p, q)->val == 1);
        assert(solution2::lowestCommonAncestor(root, p, q)->val == 1);
        assert(solution3::lowestCommonAncestor(root, p, q)->val == 1); // best
        assert(solution4::lowestCommonAncestor(root, p, q)->val == 1);
    }

}