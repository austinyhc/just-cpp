#include "0268_missing-number.h"

TEST(S, Demo) {
    Solution s;
    EXPECT_EQ(s.missingNumber(vector<int>({3,0,1})), 2);
    EXPECT_EQ(s.missingNumber(vector<int>({0,1})), 2);
    EXPECT_EQ(s.missingNumber(vector<int>({9,6,4,2,3,5,7,0,1})), 8);
}
