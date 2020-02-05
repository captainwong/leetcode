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

bool isSymmetric(TreeNode* root) {
	if (!root) { return true; }
	queue<TreeNode*> q;
	q.push(root);
	vector<int> level;
	int lc = 1, skipped_lc = 0;
	while (!q.empty()) {		
		auto p = q.front(); q.pop();
		int val = p ? p->val : -1;
		level.push_back(val);
		if (level.size() + skipped_lc >= lc) {
			auto head = level.begin();
			auto tail = level.end() - 1;
			while (head < tail) {
				if (*head++ != *tail--) { return false; }
			}
			level.clear();
			lc *= 2;
		}
		if (!p) {
			continue;
		} else if (!p->left && !p->right) {
			//skipped_lc += 2; 
			continue;
		} else {
			if (p->left) {
				q.push(p->left);
			} else {
				skipped_lc++;
			}

			if (p->right) {
				q.push(p->right);
			} else {
				skipped_lc++;
			}
		}

	}
	return true;
}

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

void traverseInL (TreeNode* p, list<int>& q)
{
	if (!p) { return; }
	if (p->left) {
		traverseInL(p->left, q);
	} else if (p->right) {
		q.push_back(-1);
	}
	q.push_back(p->val);
	if (p->right) {
		traverseInL(p->right, q);
	} else if (p->left) {
		q.push_back(-1);
	}

}

void traverseInR(TreeNode* p, list<int>& q)
{
	if (!p) { return; }
	if (p->right) {
		traverseInR(p->right, q);
	} else if (p->left) {
		q.push_back(-1);
	}
	q.push_back(p->val); 
	if (p->left) {
		traverseInR(p->left, q);
	} else if (p->right) {
		q.push_back(-1);
	}
}


bool isSymmetric2(TreeNode* root) {
	if (!root) { return true; }	
	if (root->left && root->right && root->left->val != root->right->val) { return false; }
	list<int> ql, qr;
	traverseInL(root->left, ql);
	traverseInR(root->right, qr);
	return (ql == qr);
}

int main()
{
	assert(isSymmetric2(construct(vector<int>{ 5, 4, 1, -1, 1, -1, 4, 2, -1, 2, -1 })) == false);
	assert(isSymmetric2(construct(vector<int>{ 1, 2, 2, 2, -1, 2 })) == false);
	assert(isSymmetric2(construct(vector<int>{ 1, 2, 2, 3, 4, 4, 3 })) == true);
	assert(isSymmetric2(construct(vector<int>{ 1, 2, 2, -1, 3, 3 })) == true);
	assert(isSymmetric2(construct(vector<int>{ 3, 4, 4, 5, -1, -1, 5, 6, -1, -1, 6 })) == true);
}