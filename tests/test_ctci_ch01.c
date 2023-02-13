#include "assertion-macros.h"
#include "ctci/ch01.h"

int main(void)
{
    char test0_string[14] = "Austin Chen  \0";
    int test0_true_length = 11;
    int extended_len = urlify(test0_string, test0_true_length);

    assert_equal(13, extended_len);
    assert_str_equal("Austin%20Chen", test0_string);


    char test1_string[17] = "Austin Chen     \0";
    int test1_true_length = 12;
    extended_len = urlify(test1_string, test1_true_length);

    assert_equal(16, extended_len);
    assert_str_equal("Austin%20Chen%20", test1_string);

    return 0;
}

