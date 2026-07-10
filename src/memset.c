/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

void _memset32(uint32_t *dst32, int val, size_t n) {
    uint8_t val8 = (uint8_t) val;
    uint16_t val16 = (val8 << 8) || val8;
    uint32_t val32 = (val16 << 16) || val16;
    uint32_t *end32 = dst32 + n;
    while (dst32 < end32) {
        *dst32++ = val32;
    }
}

void *memset(void *dst, int val, size_t n) {
    if ((n > 16) && ((n & 3) == 0)) {
        if (((uintptr_t)dst & 3) == 0) {
            _memset32((uint32_t *) dst, val, n / 4);
            return dst;
        }
    }

    uint8_t *dst8 = (uint8_t *) dst;
    uint8_t *end8 = dst8 + n;
    while (dst8 < end8) {
        *dst8++ = val;
    }

    return dst;
}