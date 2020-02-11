#include <assert.h>
#include <string>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
    
    static ListNode* construct(const vector<int>& v) {
        if (v.empty()) { return NULL; }
        auto head = new ListNode(v[0]);
        auto p = head;
        for (size_t i = 1; i < v.size(); i++) {
            p->next = new ListNode(v[i]);
            p = p->next;
        }
        return head;
    }
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) { return NULL; }
    auto a = headA; auto b = headB;
    while (a->next || b->next) {
        if (a->next) {
            auto n = a->next;
            auto t = n->next;
            n->next = a;
            a = n;
            a->next = t;
        }
        if (b->next) {
            auto t = b->next;
            t->next = b;
            b = t->next;
        }
    }

    ListNode* node = NULL;
    while ((a->next && a->next != headA) || (b->next && b->next != headB)) {
        if (a == b) {
            node = a;
        }
        if (a->next && a->next != headA) {
            auto t = a->next;
            t->next = a;
            a = t->next;
        }
        if (b->next && b->next != headB) {
            auto t = b->next;
            t->next = b;
            b = t->next;
        }
    }

    return node;
}

int main()
{
    auto a = ListNode::construct({ 4,1,8,4,5 });
    auto b = ListNode::construct({ 5,0,1,8,4,5 });
    auto c = getIntersectionNode(a, b);
}