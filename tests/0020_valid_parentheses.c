#include <assert.h>
#include "0020_valid_parentheses.h"

int main(void)
{
    char test_case_0[] = "()";
    assert(isValid(test_case_0));

    char test_case_1[] = "(){[]}";
    assert(isValid(test_case_1));

    char test_case_2[] = ")";
    assert(!isValid(test_case_2));

    char test_case_3[] = "[";
    assert(!isValid(test_case_3));

    char test_case_4[] = "()]";
    assert(!isValid(test_case_4));

    char test_case_5[] = "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}";
    assert(isValid(test_case_5));

    char test_case_6[] = "([{}])[](((()))){{{}}}[]";
    assert(isValid(test_case_6));

    char test_case_7[] = "(((((((((((({{{{}}}}";
    assert(!isValid(test_case_7));

    return 0;
}

