
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

int urlify(char* s, int true_length)
{
    int num_of_space = 0;
    for (int i=0; i<true_length; ++i) {
        if (s[i] == ' ') num_of_space++;
    }

    int extended_length = true_length + 2 * num_of_space;
    int i = true_length-1;

    for (int j = extended_length-1; j >= 0; j--) {
        if (s[i] == ' ') {
            s[j--] = '0';
            s[j--] = '2';
            s[j] = '%';
        } else {
            s[j] = s[i];
        }
        i--;
    }
    return extended_length;
}

#ifdef __cplusplus
}
#endif
