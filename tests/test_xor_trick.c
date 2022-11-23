#include <assert.h>
#include "xor.h"

int main(void)
{
    int testcase1[2] = {3,2};
    assert(findOneMissingValue(testcase1, 2) == 1);

    int testcase2[5] = {2,1,4,6,5};
    assert(findOneMissingValue(testcase2, 5) == 3);

    int testcase3[6] = {6,3,4,5,2,1};
    assert(findOneMissingValue(testcase3, 6) == 7);

    int testcase4[3] = {2,2,1};
    assert(findOneDuplicateValue(testcase4, 3) == 2);

    int testcase5[8] = {1,2,3,3,4,5,6,7};
    assert(findOneDuplicateValue(testcase5, 8) == 3);

    int testcase_6[11] = {1,2,3,4,5,6,7,9,10,11,13};
    int result[2] = {0};
    findTwoMissingValues(testcase_6, 11, result);
    assert(result[0] == 8);
    assert(result[1] == 12);

    return 0;
}


