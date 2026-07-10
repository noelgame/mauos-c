/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

char *strncpy(char *dst, const char *src, size_t n) {
    const uint8_t *src8 = (const uint8_t *) src;
    uint8_t *dst8 = (uint8_t *) dst;
    while(n) {
        uint8_t val = *src8++;
        *dst8++ = val;
        if (val == 0) {
            break;
        }
        n--;
    };
    return dst;
}