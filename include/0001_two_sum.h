
#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <uthash.h>

typedef struct {
	int key, index;
	UT_hash_handle hh;
} HashElement;

int* two_sum(int* nums, int numsSize, int target, int* returnSize)
{
    HashElement *hash = NULL, *elem;

    *returnSize = 2;
    int *result = (int*) calloc(*returnSize, sizeof(int));

    if (!numsSize || !nums) return result;

    for (int i = 0; i < numsSize; i++) {

        int to_find = target - nums[i];

        HASH_FIND_INT(hash, &to_find, elem);
        if (elem) {
            result[0] = elem->index;
            result[1] = i;
            return result;
        }

        elem = malloc(sizeof(HashElement));
        elem->key = nums[i];
        elem->index = i;
        HASH_ADD_INT(hash, key, elem);
    }

    *returnSize = 0;

    HashElement* tmp;
    HASH_ITER(hh, hash, elem, tmp) { free(elem); }
    return 0;
}
