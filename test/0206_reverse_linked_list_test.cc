#include "0206_reverse_linked_list.h"

using std::vector;

TEST(_206, reverse_list) {
    Solution s;
    vector<int> test = {1,3,4,2,2};
    ListNode* list = ListNode::Factory(test);
    EXPECT_EQ(ListNode::Dump(list), test);
    reverse(test.begin(), test.end());
    EXPECT_EQ(ListNode::Dump(s.reverseList(list)), test);
}

TEST(_206, sum_of_naturl_number) {
    Solution s;
    EXPECT_EQ(s.sum_of_natural_number(3),    (3+1)*3/2);
    EXPECT_EQ(s.sum_of_natural_number(100),  (100+1)*100/2);
    EXPECT_EQ(s.sum_of_natural_number(1221), (1221+1)*1221/2);
}
