#include "0236_lowest_common_ancestor_of_a_bst.h"

TEST(_236, lowest_common_ancestor_of_a_bst) {
    Solution s;
    EXPECT_EQ(
        TreeNode::DumpTree(
            s.lowestCommonAncestor(
            TreeNode::Factory(
                "[100,"
                "80,120,"
                "50,90,110,140,"
                "30,60,85,95,null,115,null,150]"),
            TreeNode::Factory("[30]"),
            TreeNode::Factory("[85]"))),
        TreeNode::DumpTree(
            TreeNode::Factory("[80,50,90,30,60,85,95]")));

    EXPECT_EQ(
        TreeNode::DumpTree(
            s.lowestCommonAncestor(
            TreeNode::Factory(
                "[100,"
                "80,120,"
                "50,90,110,140,"
                "30,60,85,95,null,115,null,150]"),
            TreeNode::Factory("[85]"),
            TreeNode::Factory("[95]"))),
        TreeNode::DumpTree(
            TreeNode::Factory("[90,85,95]")));

}

TEST(_236, is_same_tree) {
    Solution s;
    EXPECT_EQ(
            s.isSameTree(TreeNode::Factory(
            "[100,"
            "80,120,"
            "50,90,110,140,"
            "30,60,85,95,null,115,null,150]"),
                         TreeNode::Factory(
            "[100,"
            "120,80,"
            "140,110,90,50,"
            "150,null,115,null,95,85,60,30]")), false);
}
