#include "0110_balanced_binary_tree.h"

TEST(_0110, balanced_binary_tree) {
    Solution s;
    EXPECT_EQ(s.isBalanced(TreeNode::Factory("[3,9,20,null,null,15,7]")), true);
    EXPECT_EQ(s.isBalanced(TreeNode::Factory("[1,2,2,3,3,null,null,4,4]")), false);
    EXPECT_EQ(s.isBalanced(TreeNode::Factory("[]")), true);
}

TEST(_0110, height) {
    Solution s;
    EXPECT_EQ(s.height(TreeNode::Factory("[3,9,20,null,null,15,7]")), 3);
    EXPECT_EQ(s.height(TreeNode::Factory("[1,2,2,3,3,null,null,4,4]")), 4);
    EXPECT_EQ(s.height(TreeNode::Factory("[7]")), 1);
    EXPECT_EQ(s.height(TreeNode::Factory("[]")), 0);
}

