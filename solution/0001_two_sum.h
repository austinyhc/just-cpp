#include "base.h"

using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> twoSum(const vector<int>& nums, int target) {

        int length = nums.size();
        unordered_map<int, int> hash;

        for (int i = 0; i < length; ++i) {
            int res = target - nums[i];
            if (hash.count(res) > 0) {
                return vector<int>({hash[res], i});
            }
            hash[nums[i]] = i;
        }

        return vector<int>();
    }
};
