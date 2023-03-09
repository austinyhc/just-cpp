#include "utils/base.h"

typedef base::TreeNode<int> TreeNode;

class Solution {
public:
    bool isValidBST(TreeNode* root) {

        TreeNode* prev = nullptr;
        return inorder_running_compare(root, prev);
    }
    

    bool inorder_running_compare(TreeNode* root, TreeNode* prev) {

        if (!root) return true;

        if (!inorder_running_compare(root->left, prev))
            return false;

        if (prev && prev->val > root->val) return false;
        prev = root;

        return inorder_running_compare(root->right, prev);
    }


    TreeNode* insertBST(TreeNode* root, int val) {

        if (root == nullptr) {
            TreeNode* new_node = new TreeNode();
            new_node->val = val;
            return new_node;
        }

        if (val < root->val)
            root->left = insertBST(root->left, val);

        if (val > root->val)
            root->right = insertBST(root->right, val);

        return root;
    }
};
