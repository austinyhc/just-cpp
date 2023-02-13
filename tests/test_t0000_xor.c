#include <assert.h>
#include "topics/0000_xor.h"

int main(void)
{
    int testcase1[2] = {3,2};
    assert(find_one_missing_value(testcase1, 2) == 1);

    int testcase2[5] = {2,1,4,6,5};
    assert(find_one_missing_value(testcase2, 5) == 3);

    int testcase3[6] = {6,3,4,5,2,1};
    assert(find_one_missing_value(testcase3, 6) == 7);

    int testcase4[3] = {2,2,1};
    assert(find_one_dup_value(testcase4, 3) == 2);

    int testcase5[8] = {1,2,3,3,4,5,6,7};
    assert(find_one_dup_value(testcase5, 8) == 3);

    int testcase_6[11] = {1,2,3,4,5,6,7,9,10,11,13};
    int result[2] = {0};
    find_two_missing_values(testcase_6, 11, result);
    assert(result[0] == 8);
    assert(result[1] == 12);

    return 0;
}


