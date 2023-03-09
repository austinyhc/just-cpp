#include "utils/base.h"

typedef base::ListNode<int> ListNode;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        if (!head || !head->next) { return head; }

        ListNode* p = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
    
    int sum_of_natural_number(int n) {
        if (n == 0) return 0;
        return n + sum_of_natural_number(n-1);
    }
};
