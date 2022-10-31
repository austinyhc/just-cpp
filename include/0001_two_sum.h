#ifndef AUSTINCHN_TWO_SUM_H
#define AUSTINCHN_TWO_SUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>


int* solution(int* nums, int numsSize, int target, int* returnSize)
{
    int *res = calloc((*returnSize=2), sizeof(int));

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
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // AUSTINCHN_TWO_SUM_H
