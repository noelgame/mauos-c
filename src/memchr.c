/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

void *memchr(const void *src, int val, size_t n) {
    uint8_t *src8 = (uint8_t*) src;
    uint8_t *end8 = src8 + n;
    uint8_t val8 = (uint8_t) val;

    while (src8 < end8) {
        if (*src8++ == val8) {
            return (void *) src8;
        }
    }
    return NULL;
}