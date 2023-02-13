#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int find_one_missing_value(int* nums, int numsSize)
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

int find_one_dup_value(int* nums, int numsSize)
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

void find_two_missing_values(int* nums, int numsSize, int* res)
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
