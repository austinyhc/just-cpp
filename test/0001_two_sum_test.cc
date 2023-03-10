#include "0001_two_sum.h"

using std::vector;

TEST(S, Demo) {
    Solution s;
    EXPECT_EQ(s.twoSum(vector<int>({2,7,11,15}), 9), vector<int>({0,1}));
    EXPECT_EQ(s.twoSum(vector<int>({3,2,4}), 6), vector<int>({1,2}));
    EXPECT_EQ(s.twoSum(vector<int>({1,2,3,4}), 4), vector<int>({0,2}));
    EXPECT_EQ(s.twoSum(vector<int>({1,2,3,4}), 9), vector<int>());
    EXPECT_EQ(s.twoSum(vector<int>({1,2,3,4}), 5), vector<int>({1,2}));
}
