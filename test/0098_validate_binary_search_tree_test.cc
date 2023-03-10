#include "0098_validate_binary_search_tree.h"
#include "utils/tree.h"

using std::vector;

TEST(S, is_valid_bst) {
    Solution s;

    EXPECT_EQ(s.isValidBST(
        TreeNode::Factory(
            "[2,1,3]")),
              true);

    EXPECT_EQ(s.isValidBST(
        TreeNode::Factory(
            "[5,1,4,null,null,3,6]")),
              false);

    EXPECT_EQ(s.isValidBST(
        TreeNode::Factory(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]")),
              true);
}

TEST(S, insert_bst) {
    Solution s;
    TreeNode* t = TreeNode::Factory(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]");

    EXPECT_EQ(
            TreeNode::DumpTree(s.insertBST(t, 105)),
            vector<int>({100,80,120,50,90,110,140,30,60,85,95,105,115,150}));
}
