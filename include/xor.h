
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int findOneMissingValue(int* nums, int numsSize)
{
    int result = 0;
    for (int i = 1; i <= numsSize+1; ++i) {
        result ^= i;
    }

    for (int i = 0; i < numsSize; ++i) {
        result ^= nums[i];
    }
    return result;
}

int findOneDuplicateValue(int* nums, int numsSize)
{
    int result = 0;
    for (int i = 1; i < numsSize; ++i) {
        result ^= i;
    }
    for (int i = 0; i < numsSize; ++i) {
        result ^= nums[i];
    }
    return result;
}

void findTwoMissingValues(int* nums, int numsSize, int* res)
{
    int result = 0;
    for (int i = 1; i <= numsSize+2; ++i) {
        result ^= i;
    }
    for (int i = 0; i < numsSize; ++i) {
        result ^= nums[i];
    }

    int set_bit_no = result & ~(result-1);

    int x = 0, y = 0;
    for (int i = 1; i <= numsSize+2; ++i) {
        if (i & set_bit_no)
            x ^= i;
        else
            y ^= i;
    }
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] & set_bit_no)
            x ^= nums[i];
        else
            y ^= nums[i];
    }

    res[0] = x < y ? x : y;
    res[1] = x < y ? y : x;
}

#ifdef __cplusplus
}
#endif
