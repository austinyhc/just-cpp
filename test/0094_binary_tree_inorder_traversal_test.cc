#include "0094_binary_tree_inorder_traversal.h"

TEST(S, Demo) {
    Solution s;
    TreeNode* t = base::TreeNodeFactory<int>("[1,2,3,4,5,null,6]");
    EXPECT_EQ(s.inorderTraversal(t), vector<int>({4,2,5,1,3,6}));
}
