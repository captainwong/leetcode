#include "../common/ListNode.h"


ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    stack<ListNode*> sa, sb;
    auto a = headA;
    auto b = headB;
    while (a) {
        sa.push(a);
        a = a->next;
    }
    while (b) {
        sb.push(b);
        b = b->next;
    }

    ListNode* p = NULL;
    while (!sa.empty() && !sb.empty()) {
        a = sa.top(); sa.pop();
        b = sb.top(); sb.pop();
        if (a == b || a->val == b->val) {
            p = a;
        } else {
            break;
        }
    }
    return p;
}

int main()
{
    assert(ListNode::equals(
            getIntersectionNode(ListNode::construct({ 4,1,8,4,5 }), 
                                ListNode::construct({ 5,0,1,8,4,5 })), 
            ListNode::construct({ 1,8,4,5 })
        )
    );
}
