
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>

int* two_sum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *res = calloc(*returnSize, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int x = target - nums[i];
        for (int j = i+1; j<numsSize; j++) {
            if (x == nums[j]) {
                res[0] = i;
                res[1] = j;
                return res;
            }
        }
    }

    *returnSize = 0;
    return 0;
}

#ifdef __cplusplus
}
#endif
