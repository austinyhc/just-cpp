#include "1018_binary_prefix_divisible.h"

TEST(_1018, binary_prefix_divisible) {
    Solution s;
    EXPECT_EQ(s.prefixesDivBy5(vector<int>({0,1,1})), vector<bool>({true, false, false}));
    EXPECT_EQ(s.prefixesDivBy5(vector<int>({1,1,0,1,0,1,1})), vector<bool>({false, false, false, false, false, false, false}));
    // EXPECT_EQ(s.prefixesDivBy5(vector<int>(
    //           {1,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,1,0})),
    //           vector<bool>({false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,false}));
}

