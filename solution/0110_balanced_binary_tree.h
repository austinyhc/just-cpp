#include "tree.h"
#include "base.h"

typedef leetlib::TreeNode<int> TreeNode;

class Solution {
public:
    bool isBalanced(TreeNode* root) {

        if (root == nullptr) return true;
        int H_R = height(root->right);
        int H_L = height(root->left);
        int diff = std::abs((H_R - H_L));
        if (diff > 1) return false;

        if (!isBalanced(root->left)) return false;
        if (!isBalanced(root->right)) return false;

        return true;
    }

    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
};
