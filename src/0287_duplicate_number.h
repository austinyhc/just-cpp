#include <unordered_map>
#include "utils/base.h"

using std::vector;
using std::unordered_map;

class Solution {
public:
    int findDuplicate(const vector<int>& nums) {

        unordered_map<int,int> dict;

        for (int const& num : nums) {
            if (dict.count(num)) dict[num]++;
            else dict.insert({num, 1});
        }

        for (auto& kv : dict) {
            if (kv.second > 1) return kv.first;
        }
        return -1;
    }
};
