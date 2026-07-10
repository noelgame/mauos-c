/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

int strcmp(const char *srcA, const char *srcB) {
    do {
        int8_t A = *srcA++;
        int8_t B = *srcB++;
        if (A != B) {
            return A-B;
        }

        if (A == 0) {
            break;
        }
    } while (1);
    return 0;
}