// 2.add-two-numbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cassert>
#include "../leetcode.h"

using namespace leetcode;

// https://leetcode-cn.com/problems/add-two-numbers/
/*
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/


// 不可行，可能超越int, long, long long 范围
//class Solution1 {
//public:
//	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//		long long sum = decode(l1) + decode(l2);
//		return encode(sum);
//	}
//
//	long long decode(ListNode* l) {
//		long long i = 0, sum = 0;
//		while (l) {
//			sum += l->val * pow(10, i++);
//			l = l->next;
//		}
//		return sum;
//	};
//
//	ListNode* encode(long long n) {
//		auto ret = new ListNode(0);
//		ret->val = n % 10;
//		n /= 10;
//		auto tmp = ret;
//		while (n) {
//			auto l = new ListNode(0);
//			l->val = n % 10;
//			tmp->next = l;
//			tmp = l;
//			n /= 10;
//		}
//		return ret;
//	}
//
//	void test() {
//		auto l1 = encode(9);
//		auto l2 = encode(9999999991);
//		auto l3 = addTwoNumbers(l1, l2);
//		// 只能到这里了，总有更大的数超过long long 范围
//	}
//};


class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int carry = 0;

		auto all_valid = [](ListNode*& l1, ListNode*& l2, int& carry) {
			auto p = new ListNode(0);
			int sum = l1->val + l2->val + carry;
			if (sum > 9) {
				p->val = sum - 10;
				carry = 1;
			} else {
				p->val = sum;
				carry = 0;
			}
			l1 = l1->next;
			l2 = l2->next;
			return p;
		};

		auto one_valid = [](ListNode*& l, int& carry) {
			auto p = new ListNode(0);
			int sum = l->val + carry;
			if (sum > 9) {
				p->val = sum - 10;
				carry = 1;
			} else {
				p->val = sum;
				carry = 0;
			}
			l = l->next;
			return p;
		};

		auto ret = all_valid(l1, l2, carry);
		auto p = ret;
		
		while (l1 || l2) {
			if (l1 && l2) {
				p->next = all_valid(l1, l2, carry);
				p = p->next;
			} else if (l1) {
				p->next = one_valid(l1, carry);
				p = p->next;
			} else if (l2) {
				p->next = one_valid(l2, carry);
				p = p->next;
			}
		}

		if (carry) {
			p->next = new ListNode(1);
		}

		return ret;
	}

	ListNode* addTwoNumbersMaximized(ListNode* l1, ListNode* l2) {
		int carry = 0;
		auto dummy = new ListNode(0);
		auto p = dummy;

		while (l1 || l2) {
			int x = l1 ? l1->val : 0;
			int y = l2 ? l2->val : 0;
			int sum = x + y + carry;
			carry = sum / 10;
			auto q = new ListNode(sum % 10);
			p->next = q;
			p = q;
			if (l1) { l1 = l1->next; }
			if (l2) { l2 = l2->next; }
		}

		if (carry) {
			p->next = new ListNode(1);
		}

		return dummy->next;
	}

	bool test(std::initializer_list<int> l1, std::initializer_list<int> l2, std::initializer_list<int> l3) {
		auto nl1 = makeList(l1);
		auto nl2 = makeList(l2);
		auto nl3 = makeList(l3);
		auto nl12 = addTwoNumbersMaximized(nl1, nl2);
		printList("nl1", nl1);
		printList("nl2", nl2);
		printList("nl3", nl3);
		printList("nl12", nl12);
		return isEqual(nl12, nl3);
	}
};

int main()
{
	Solution s;
	assert(s.test({ 9 }, 
				  { 1,9,9,9,9,9,9,9,9,9 },
				  { 0,0,0,0,0,0,0,0,0,0,1 }));

	assert(s.test({ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				  { 5, 6, 4 }, 
				  { 6,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 }));

	assert(s.test({ 2,4,3 }, 
				  { 5,6,4 }, 
				  { 7,0,8 }));
	
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
