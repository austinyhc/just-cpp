#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

int get_successor_value(struct TreeNode* root) {
    root = root->right;
    while (root->left) root = root->left;
    return root->value;
}

int get_predecessor_value(struct TreeNode* root) {
    root = root->left;
    while (root->right) root = root->right;
    return root->value;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key){
    if (root == NULL)
        return root;

    if (key < root->value) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->value) {
        root->right = deleteNode(root->right, key);
    } else {

        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            struct TreeNode* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            struct TreeNode* temp = root;
            root = root->left;
            free(temp);
        } else {
            // 2 children - get min node of right subtree
            // int right_min = get_min(root->right);
            // root->value = right_min;
            // root->right = deleteNode(root->right, right_min);
        }
    }
    return root;
}

#ifdef __cplusplus
}
#endif
