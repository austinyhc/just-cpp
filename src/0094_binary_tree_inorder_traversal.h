
#include "utils/base.h"
typedef base::TreeNode<int> TreeNode;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        inorder(root, ret);
        return ret;
    }

    void inorder(TreeNode* root, vector<int>& result) {
        if (root == nullptr) return;

        if (root->left) inorder(root->left, result);
        result.push_back(root->val);
        if (root->right) inorder(root->right, result);
    }
};
