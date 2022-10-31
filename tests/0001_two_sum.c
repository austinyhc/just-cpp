#include <assert.h>
#include "0001_two_sum.h"

int main(void)
{
    int nums[4] = {2,7,11,15};
    int target = 9;
    int returnSize;
    int *results;
    results = solution(nums, 4, target, &returnSize);

    assert(returnSize == 2);
    assert(results[0] == 0);
    assert(results[1] == 1);
    return 0;
}

