#pragma once
#include <ios>

namespace leetcode {
    
static const auto __fastIO = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

static ListNode* makeList(std::initializer_list<int> n) {
	auto ret = new ListNode(0);
	auto p = ret;
	for (auto i : n) {
		auto l = new ListNode(i);
		p->next = l;
		p = l;
	}
	p = ret->next;
	delete ret;
	return p;
}

static bool isEqual(ListNode* l1, ListNode* l2) {
	while (l1 || l2) {
		if (!l1 || !l2) { return false; }
		if (l1->val != l2->val) { return false; }
		l1 = l1->next;
		l2 = l2->next;
	}
	return true;
}

static void printList(const char* tag, ListNode* l) {
	printf("%s:[", tag);
	while (l) {
		printf("%d, ", l->val);
		l = l->next;
	}
	printf("]\n");
}

}

