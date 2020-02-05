#include <queue>
#include <stack>
#include <assert.h>
#include <list>

using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* construct(const vector<int>& v) {
	auto root = new TreeNode(v[0]);
	vector<TreeNode*> level;
	level.push_back(root);
	for (size_t i = 1; i < v.size(); ) {
		vector<TreeNode*> tmp;
		for (auto& p : level) {
			if (p && p->val != -1) {
				TreeNode* left = p->left = (i >= v.size() || v[i] == -1) ? nullptr : new TreeNode(v[i]); i++;
				TreeNode* right = p->right = (i >= v.size() || v[i] == -1) ? nullptr : new TreeNode(v[i]); i++;
				tmp.push_back(left);
				tmp.push_back(right);
			}
		}
		level = tmp;
	}
	return root;
}

int getDepth(TreeNode* p, int d) {
    if (!p) { return d; }
    int d1 = getDepth(p->left, d + 1);
    int d2 = getDepth(p->right, d + 1);
    return max(d1, d2);
}

int getDepth2(TreeNode* p, int d) {
    if (!p)return d;
    while (p) {
        if (p->left && p->right) {
            int d1 = getDepth2(p->left, d+1);
            int d2 = getDepth2(p->right, d+1);
            return d = max(d1, d2);
        } else if (p->left) {
            p = p->left;
            d++;
        } else if (p->right) {
            p = p->right;
            d++;
        } else {
            break;
        }
    }
    return d;
}

int maxDepth(TreeNode* root) {
    if (!root) { return 0; }
    int d = 1;
    return getDepth2(root, d);
}

int main()
{
    assert(maxDepth(construct({ 3,9,20,-1,-1,15,7 })) == 3);
}