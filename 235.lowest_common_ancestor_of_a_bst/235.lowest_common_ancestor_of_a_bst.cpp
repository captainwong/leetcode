#include "../common/TreeNode.h"


/*
执行用时 :28 ms, 在所有 C++ 提交中击败了39.72%的用户
内存消耗 :17.6 MB, 在所有 C++ 提交中击败了23.70%的用户
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
执行用时 :40 ms, 在所有 C++ 提交中击败了14.66%的用户
内存消耗 :19.9 MB, 在所有 C++ 提交中击败了16.40%的用户
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
执行用时 :16 ms, 在所有 C++ 提交中击败了95.93%的用户
内存消耗 :17 MB, 在所有 C++ 提交中击败了29.02%的用户
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
执行用时 :24 ms, 在所有 C++ 提交中击败了61.96%的用户
内存消耗 :17.7 MB, 在所有 C++ 提交中击败了23.64%的用户
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