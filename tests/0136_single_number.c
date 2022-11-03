#include <assert.h>
#include "0136_single_number.h"

int main(void)
{
    int testcase1[3] = {2,2,1};
    assert(singleNumber(testcase1, 3) == 1);

    int testcase2[5] = {4,1,2,1,2};
    assert(singleNumber(testcase2, 5) == 4);

    int testcase3[1] = {1};
    assert(singleNumber(testcase3, 1) == 1);
    return 0;
}


