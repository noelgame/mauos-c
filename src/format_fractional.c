/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <format.h>

#include <attributes.h>
#include <errno.h>
#include <string.h>

int __weak format_fractional(char *dst, uint8_t flags, double num) {
        if (dst == NULL) {
            return -(int)EINVAL;
        }
    
        if ((num >= 1000000.0) || (num <= -1000000.0)) {
            // For simplicity, we won't handle very large/small numbers in this stub.
            return -(int)EINVAL;
        }

        int64_t int_part = (int64_t)num;
        double frac_part = num - (double)int_part;
    
        int idx = format_integer(dst, 10, flags, int_part);

        // Add the decimal point.
        dst[idx++] = '.';
    
        // Format the fractional part. For simplicity, we will just take 6 digits after the decimal point.
        for (int i = 0; i < 6; i++) {
            frac_part *= 10;
            int digit = (int)frac_part;
            dst[idx++] = '0' + digit;
            frac_part -= digit;
        }
    
        dst[idx] = '\0';
        return idx;
}
