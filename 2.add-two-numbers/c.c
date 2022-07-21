#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../c/ListNode.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* res = NULL, * cur = NULL;
    int i = 0, j = 0, carry = 0;
    res = malloc(sizeof(*res));
    res->next = NULL;
    res->val = 0;
    cur = res;

    while (l1 || l2) {
        int a = 0, b = 0;
        if (l1) {
            a = l1->val;
            l1 = l1->next;
        }
        if (l2) {
            b = l2->val;
            l2 = l2->next;
        }
        int c = a + b + carry;
        if (c > 9) {
            carry = c / 10;
            c %= 10;
        } else {
            carry = 0;
        }

        struct ListNode* p = NULL;
        p = malloc(sizeof(*res));
        p->next = NULL;
        p->val = c;

        cur->next = p;
        cur = p;
    }

    if (carry > 0) {
        struct ListNode* p = NULL;
        p = malloc(sizeof(*res));
        p->next = NULL;
        p->val = carry;

        cur->next = p;
        cur = p;
    }

    if (res->next) {
        return res->next;
    }

    return res;
}

int main()
{
	int a1[] = { 2,4,9 };
	int a2[] = { 5,6,4,9 };
	int a3[] = { 7,0,4,0,1 };
	struct ListNode* l1 = listNew(a1, sizeof(a1) / sizeof(a1[0]));
	struct ListNode* l2 = listNew(a2, sizeof(a2) / sizeof(a2[0]));
	struct ListNode* ex = listNew(a3, sizeof(a3) / sizeof(a3[0]));
	struct ListNode* l3 = addTwoNumbers(l1, l2);
	
	assert(listEqual(l3, ex));
}