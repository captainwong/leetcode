#pragma once

#include "leetcode.h"


struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}

    static ListNode* construct(std::initializer_list<int> n) {
        if (n.size() == 0) { return nullptr; }
        auto i = n.begin();
        auto head = new ListNode(*i);
        auto p = head;
        while (++i != n.end()) {
            p->next = new ListNode(*i);
            p = p->next;
        }
        return head;
    }

    static ListNode* construct(const vector<int>& v) {
        if (v.empty()) { return nullptr; }
        auto head = new ListNode(v[0]);
        auto p = head;
        for (size_t i = 1; i < v.size(); i++) {
            p->next = new ListNode(v[i]);
            p = p->next;
        }
        return head;
    }


    static bool equals(ListNode* l1, ListNode* l2) {
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
};