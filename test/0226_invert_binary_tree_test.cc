#include "0226_invert_binary_tree.h"

TEST(S, invert_binary_tree) {
    Solution s;

    EXPECT_EQ(s.invertTree(
        base::TreeNodeFactory<int>(
            "[2,1,3]")),
              true);

    EXPECT_EQ(s.invertTree(
        base::TreeNodeFactory<int>(
            "[5,1,4,null,null,3,6]")),
              false);

    EXPECT_EQ(s.invertTree(
        base::TreeNodeFactory<int>(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]")),
              true);
}
