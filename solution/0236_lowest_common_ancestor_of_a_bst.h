#include <base.h>
#include <tree.h>

typedef leetlib::TreeNode<int> TreeNode;

class Solution {
public:

    bool isSameTree(TreeNode* p, TreeNode* q) {

        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false;

        return (p->val == q->val &&
                isSameTree(p->right, q->right) &&
                isSameTree(p->left, q->left));
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (root == nullptr || isSameTree(root, p) || isSameTree(root, q))
            return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left == nullptr) return right;
        else if (right == nullptr) return left;
        else return root;
    }
};
