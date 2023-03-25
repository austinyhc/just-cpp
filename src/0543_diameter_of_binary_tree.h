#include "utils/base.h"
#include "utils/tree.h"

typedef leetlib::TreeNode<int> TreeNode;

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int H_L = height(root->left);
        int H_R = height(root->right);
        int n_path = H_L + H_R;
        int MAX = std::max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right));
        if (n_path > MAX) return n_path;
        return MAX;
    }

    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
};
