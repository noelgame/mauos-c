/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

void _memcpy32(uint32_t *dst32, const uint32_t *src32, size_t n) {
    uint32_t *end32 = dst32 + n;
    while (dst32 < end32) {
        *dst32++ = *src32++;
    }
}

void *memcpy(void *dst, const void *src, size_t n) {
    if ((n > 16) && ((n & 3) == 0)) {
        if ((((uintptr_t)dst & 3) == 0) &&  (((uintptr_t)src & 3) == 0)) {
            _memcpy32((uint32_t *) dst, (const uint32_t *) src, n / 4);
            return dst;
        }
    }

    const uint8_t *src8 = (const uint8_t *) src;
    uint8_t *dst8 = (uint8_t *) dst;
    uint8_t *end8 = dst8 + n;
    while (dst8 < end8) {
        *dst8++ = *src8++;
    }

    return dst;
}