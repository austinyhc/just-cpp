#include "0226_invert_binary_tree.h"

TEST(_226, invert_binary_tree) {
    Solution s;

    EXPECT_EQ(
            TreeNode::DumpTree(s.invertTree(TreeNode::Factory("[2,1,3]"))),
            TreeNode::DumpTree(TreeNode::Factory("[2,3,1]")));

    EXPECT_EQ(
            TreeNode::DumpTree(s.invertTree(TreeNode::Factory("[5,1,4,null,null,3,6]"))),
            TreeNode::DumpTree(TreeNode::Factory("[5,4,1,6,3,null,null]")));

    EXPECT_EQ(
            TreeNode::DumpTree(s.invertTree(TreeNode::Factory(
                                                "[100,"
                                                "80,120,"
                                                "50,90,110,140,"
                                                "30,60,85,95,null,115,null,150]"))),
            TreeNode::DumpTree(TreeNode::Factory(
                                                "[100,"
                                                "120,80,"
                                                "140,110,90,50,"
                                                "150,null,115,null,95,85,60,30]")));
}
