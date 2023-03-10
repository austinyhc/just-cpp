#pragma once

#include <string>
#include <queue>

#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"

namespace leetlib {

template<typename T>
class TreeNode {
public:
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next;

    TreeNode() :
        val(0), left(nullptr), right(nullptr), next(nullptr) {}

    TreeNode(T x) :
        val(x), left(nullptr), right(nullptr), next(nullptr) {}

    TreeNode(T x, TreeNode* left, TreeNode* right) :
        val(x), left(left), right(right) {}
};

template<typename T>
TreeNode<T>* TreeNodeFactory(const std::string& input) {

    absl::string_view list_str(input);
    std::vector<TreeNode<T>*> level_traversal;

    absl::ConsumePrefix(&list_str, "[");
    absl::ConsumeSuffix(&list_str, "]");

    if (list_str == "") {
        return nullptr;
    }

    for (auto c : absl::StrSplit(list_str, ',')) {

        while (absl::ConsumePrefix(&c, " ")) {}
        while (absl::ConsumeSuffix(&c, " ")) {}

        if (absl::AsciiStrToLower(c) == "null") {
            level_traversal.push_back(nullptr);
            continue;
        }

        T val;
        std::stringstream(std::string(c)) >> val;
        level_traversal.push_back(new TreeNode<T>(val));
    }

    size_t cur_root_idx = 0;
    int node_pos = 0;  // 0: left, 1: right
    TreeNode<T>* cur_root;
    for (size_t i = 1; i < level_traversal.size(); ++i) {
        cur_root = level_traversal[cur_root_idx];

        if (node_pos == 0) {
            cur_root->left = level_traversal[i];
        } else {
            cur_root->right = level_traversal[i];
            do {
                ++cur_root_idx;
                if (cur_root_idx > i) {
                    return level_traversal[0];
                }
            } while (!level_traversal[cur_root_idx]);
        }
        node_pos = !node_pos;
    }

    return level_traversal[0];
}

template<typename T>
std::vector<T> DumpTree(TreeNode<T>* t) {

    if (!t) return std::vector<T>();

    std::queue<TreeNode<T>*> fifo;
    fifo.push(t);

    std::vector<T> ret;

    while (!fifo.empty()) {

        TreeNode<T>* node = fifo.front();

        ret.push_back(node->val);
        fifo.pop();

        if (node->left) { fifo.push(node->left); }
        if (node->right) { fifo.push(node->right); }
    }
    return ret;
}

}  // namespace leetlib
