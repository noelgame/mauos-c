/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <format.h>

#include <attributes.h>
#include <errno.h>
#include <string.h>

const char _lower_digits[] = "0123456789abcdef";
const char _upper_digits[] = "0123456789ABCDEF";

int __weak format_integer(char *dst, int base, uint8_t flags, int64_t num) {
    int idx = 0;
    bool neg = false;
    uint64_t abs_num = num;

    if ((base < 2) || (base > 16) || (dst == NULL)) {
        return -(int)EINVAL;
    }

    if ((base == 10) && (flags & FORMAT_FLAG_UNSIGNED) == 0) {
        if (num < 0) {
            neg = true;
            abs_num = -num;
        }
    }
    
    if (num == 0) {
        dst[idx++] = '0';
    } else {
        // Add digits in reverse order.
        const char *digits = (flags & FORMAT_FLAG_UPPER) ? _upper_digits : _lower_digits;
        while(abs_num > 0) {
            int rem = abs_num % base;
            dst[idx++] = digits[rem];
            abs_num /= base;
        }
    }

    // Add sign if needed.
    if (neg) {
        dst[idx++] = '-';
    } else {
        if (flags & FORMAT_FLAG_PLUS) {
            dst[idx++] = '+';
        }
    }

    if ((base == 16) && (flags & FORMAT_FLAG_ALT)) {
        dst[idx++] = (flags & FORMAT_FLAG_UPPER) ? 'X' : 'x';
        dst[idx++] = '0';
    }

    for (int i = 0; i < idx / 2; i++) {
        char temp = dst[i];
        dst[i] = dst[idx - 1 - i];
        dst[idx - 1 - i] = temp;
    }

    dst[idx] = '\0';
    return idx;
}
