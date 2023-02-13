#include <assert.h>
#include "0001_two_sum.h"

int main(void)
{
    int returnSize;
    int *results;

    int test0_nums[4] = {2,7,11,15};
    int test0_target = 9;
    results = two_sum(test0_nums, 4, test0_target, &returnSize);

    assert(returnSize == 2);
    assert(results[0] == 0);
    assert(results[1] == 1);

    int test1_nums[3] = {3,2,4};
    int test1_target = 6;
    results = two_sum(test1_nums, 3, test1_target, &returnSize);

    assert(returnSize == 2);
    assert(results[0] == 1);
    assert(results[1] == 2);

    int test2_nums[2] = {3,3};
    int test2_target = 6;
    results = two_sum(test2_nums, 2, test2_target, &returnSize);

    assert(returnSize == 2);
    assert(results[0] == 0);
    assert(results[1] == 1);

    return 0;
}

