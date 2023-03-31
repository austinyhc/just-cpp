#pragma once

#include <vector>

#include "gtest/gtest.h"

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

template<typename T>
void DumpVector(std::vector<T> v) {
    std::cout << v;
}

