#include "0287_duplicate_number.h"

TEST(S, Demo) {
    Solution s;
    EXPECT_EQ(s.findDuplicate(vector<int>({1, 3, 4, 2, 2})), 2);
    EXPECT_EQ(s.findDuplicate(vector<int>({3, 1, 3, 4, 2})), 3);
}
