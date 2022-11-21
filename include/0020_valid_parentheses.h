
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool isValid(char *s) {

    char *reuse_ptr = s;

    for (char *iter=s; *iter; iter++) {
        switch (*iter) {
            case '(': *reuse_ptr = ')'; reuse_ptr++; continue;
            case '[': *reuse_ptr = ']'; reuse_ptr++; continue;
            case '{': *reuse_ptr = '}'; reuse_ptr++; continue;
            default: {
                if (0 == reuse_ptr-s) return false;

                char expected = *--reuse_ptr;
                if (*iter != expected) return false;
            }
        }
    }
    return 0 == reuse_ptr-s;
}

#ifdef __cplusplus
}
#endif
