#pragma once

#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

static struct ListNode* listNew(int* arr, int n) {
	if (n < 1) { return NULL; }
	struct ListNode* head = malloc(sizeof(*head)), *p;
	if (!head) return NULL;
	head->val = arr[0];
	head->next = NULL;
	p = head;
	for (int i = 1; i < n; i++) {
		struct ListNode* q = malloc(sizeof(*head));
		if (!q) {
			while (p) {
				q = p->next;
				free(p);
				p = q;
			}
			return NULL;
		}
		q->val = arr[i];
		q->next = NULL;
		p->next = q;
		p = q;
	}
	return head;
}

static void listFree(struct ListNode* li) {
	while (li) {
		struct ListNode* next = li->next;
		free(li);
		li = next;
	}
}

static int listEqual(struct ListNode* l1, struct ListNode* l2) {
	while (l1 || l2) {
		if (!l1 || !l2) return 0;
		if (l1->val != l2->val)return 0;
		l1 = l1->next;
		l2 = l2->next;
	}
	return 1;
}


