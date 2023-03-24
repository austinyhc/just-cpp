#include "utils/base.h"

using std::vector;
class Solution {

public:
    vector<bool> prefixesDivBy5(const vector<int>& nums) {

        vector<bool> ret;
        int number = 0;
        for (auto const& bit : nums) {
            number = (number * 2 + bit) % 5;
            ret.push_back(number == 0);
        }
        return ret;
    }
};
