#include "utils/base.h"

using std::vector;

class Solution {
public:
    int missingNumber(const vector<int>& nums) {
        int n = nums.size();
        int ret = 0;

        for (int i = 0; i <= n; ++i) { ret ^= i; };
        for (int const& num : nums) { ret ^= num; }

        return ret;
    }
};
