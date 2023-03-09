#include "0098_validate_binary_search_tree.h"

TEST(S, is_valid_bst) {
    Solution s;

    EXPECT_EQ(s.isValidBST(
        base::TreeNodeFactory<int>(
            "[2,1,3]")),
              true);

    EXPECT_EQ(s.isValidBST(
        base::TreeNodeFactory<int>(
            "[5,1,4,null,null,3,6]")),
              false);

    EXPECT_EQ(s.isValidBST(
        base::TreeNodeFactory<int>(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]")),
              true);
}

TEST(S, insert_bst) {
    Solution s;
    TreeNode* t = base::TreeNodeFactory<int>(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]");

    EXPECT_EQ(
            base::DumpTree(s.insertBST(t, 105)),
            vector<int>({100,80,120,50,90,110,140,30,60,85,95,105,115,150}));
}
