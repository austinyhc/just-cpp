#include "0543_diameter_of_binary_tree.h"

TEST(_0543, diameter_of_binary_tree) {
    Solution s;
    EXPECT_EQ(s.diameterOfBinaryTree(TreeNode::Factory("[3,9,20,null,null,15,7]")), 3);
    EXPECT_EQ(s.diameterOfBinaryTree(TreeNode::Factory("[1,2,3,4,5,null,null]")), 3);
    EXPECT_EQ(s.diameterOfBinaryTree(TreeNode::Factory("[1,2]")), 1);
    EXPECT_EQ(s.diameterOfBinaryTree(TreeNode::Factory("[1,2,2,3,3,null,null,4,4]")), 4);
    EXPECT_EQ(s.diameterOfBinaryTree(TreeNode::Factory("[]")), 0);
}

TEST(_0543, height) {
    Solution s;
    EXPECT_EQ(s.height(TreeNode::Factory("[3,9,20,null,null,15,7]")), 3);
    EXPECT_EQ(s.height(TreeNode::Factory("[1,2,2,3,3,null,null,4,4]")), 4);
    EXPECT_EQ(s.height(TreeNode::Factory("[7]")), 1);
    EXPECT_EQ(s.height(TreeNode::Factory("[]")), 0);
}

