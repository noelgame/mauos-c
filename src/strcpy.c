/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

char *strcpy(char *dst, const char *src) {
    const uint8_t *src8 = (const uint8_t *) src;
    uint8_t *dst8 = (uint8_t *) dst;
    do {
        uint8_t val = *src8++;
        *dst8++ = val;
        if (val == 0) {
            break;
        }
    } while(1);
    return dst;
}