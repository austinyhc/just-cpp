#include "0268_missing_number.h"

using std::vector;

TEST(_268, missing_number) {
    Solution s;
    EXPECT_EQ(s.missingNumber(vector<int>({3,0,1})), 2);
    EXPECT_EQ(s.missingNumber(vector<int>({0,1})), 2);
    EXPECT_EQ(s.missingNumber(vector<int>({9,6,4,2,3,5,7,0,1})), 8);
}
