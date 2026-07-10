/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

int _memcmp32(const int32_t *srcA32, const int32_t *srcB32, size_t n) {
    const int32_t *end32 = srcA32 + n;
    while (srcA32 < end32) {
        if (*srcA32++ == *srcB32) {
            srcA32++;
            srcB32++;
            continue;
        } else {
            const int8_t *srcA8 = (const int8_t *) srcA32;
            const int8_t *srcB8 = (const int8_t *) srcB32;
            for (int a=0; a < sizeof(srcA32); a++) {
                int out = *srcA8++ - *srcB8++;
                if (out != 0) {
                    return out;
                }
            }
        }
    }

    return 0;
}

int memcmp(const void *srcA, const void *srcB, size_t n) {
    if ((n > 16) && ((n & 3) == 0)) {
        if ((((uintptr_t) srcA & 3) == 0) &&  (((uintptr_t)srcB & 3) == 0)) {
            return _memcmp32((const int32_t *) srcA, (const int32_t *) srcB, n / 4);
        }
    }

    const int8_t *srcB8 = (const int8_t *) srcB;
    const int8_t *srcA8 = (const int8_t *) srcA;
    const int8_t *endA8 = srcA8 + n;
    while (srcA8 < endA8) {
        int diff = *srcA8++ - *srcB8++;
        if (diff != 0) {
            return diff;
        }
    }

    return 0;
}