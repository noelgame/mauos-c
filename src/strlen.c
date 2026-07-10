/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

size_t strlen(const char *src) {
    const char *start = src;
    
    while (*src != 0) {
        src++;
    }
    return src - start;
}