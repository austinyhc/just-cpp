
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "uthash.h"

bool is_unique(char* s) {
    int length = strlen(s);
    int hash[128] = {0};

    if (length == 0) return true;

    for (int i = 0; i < length; i++) {
        int pos = s[i];
        if(hash[pos] > 0) return false;
        else hash[pos]++;
    }
    return true;
}

typedef struct {
    char letter;
    int count;
    UT_hash_handle hh;
} HashElement;

bool check_permutation(char* a, char* b) {
    int len_of_a = strlen(a);
    int len_of_b = strlen(b);

    if (len_of_a != len_of_b) return false;

    HashElement* hash = NULL, *elem;

    for (int i = 0; i < len_of_a; ++i) {
        int to_find = (int)*(a+i);
        HASH_FIND_INT(hash, &to_find, elem);
        if (elem) {
            elem->count++;
        } else {
            elem = malloc(sizeof(HashElement));
            elem->letter = *(a+i);
            elem->count = 1;
            HASH_ADD_INT(hash, letter, elem);
        }
    }

    for (int i = 0; i < len_of_b; ++i) {
        int to_find = (int)*(b+i);
        HASH_FIND_INT(hash, &to_find, elem);
        if (!elem) return false;

        elem->count--;
        if (elem->count < 0) return false;
    }
    return true;
}

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
