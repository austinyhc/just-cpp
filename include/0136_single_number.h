#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int singleNumber(int *nums, int numSize)
{
    if (numSize == 1) return nums[numSize-1];

    int result = 0;
    for (int i = 0; i < numSize; i++)
        result ^= nums[i];

    return result;
}

#ifdef __cplusplus
}
#endif
