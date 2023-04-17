#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace leetlib {

template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode() : next(NULL) {}
    ListNode(T x) : val(x), next(NULL) {}

    static ListNode* Factory(const std::initializer_list<T> l);
    static ListNode* Factory(const std::vector<T> l);
    static std::vector<T> Dump(ListNode* head);

};

template <typename T>
ListNode<T>* ListNode<T>::Factory(const std::initializer_list<T> l) {
    if (l.size() == 0) return nullptr;
    auto iter = l.begin();
    ListNode* cur = new ListNode(*iter);
    ListNode* ret = cur;
    ++iter;
    while (iter != l.end()) {
        cur->next = new ListNode(*iter);
        cur = cur->next;
        ++iter;
    }
    return ret;
}

template <typename T>
ListNode<T>* ListNode<T>::Factory(const std::vector<T> l) {
    if (l.size() == 0) return nullptr;
    auto iter = l.begin();
    ListNode* cur = new ListNode(*iter);
    ListNode* ret = cur;
    ++iter;
    while (iter != l.end()) {
        cur->next = new ListNode(*iter);
        cur = cur->next;
        ++iter;
    }
    return ret;
}

template <typename T>
std::vector<T> ListNode<T>::Dump(ListNode* head) {
    std::vector<T> ret;
    while (head) {
        ret.push_back(head->val);
        head = head->next;
    }
    return ret;
}

template<typename T>
struct BiDirListNode {
    T val;
    BiDirListNode* prev;
    BiDirListNode* next;
    BiDirListNode() : prev(NULL), next(NULL) {}
    BiDirListNode(T x) : val(x), prev(NULL), next(NULL) {}
};

} // namespace leetlib
