/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Host-side tests for the parsing helpers in src/format.c (system libc for I/O).
 * Build: make test-format
 *
 * Note: that target compiles src/format.c together with this file, so
 * inc/format.h must stay consistent with format.c (types and declarations).
 * Contract for format_convertion (see src/format.c): the fmt argument is the
 * substring immediately after a single leading percent sign from the original
 * format string. For a literal percent ("%%"), pass a string whose first
 * character is '%'; the function then returns 1 and sets conversion to '%'.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <format.h>

int main() {
    char buf[64];

    // Test decimal formatting.
    int len = format_integer(buf, 10, 0, 12345);
    buf[len] = '\0';
    printf("Decimal: %s\n", buf); // Expected: "12345"

    // Test hexadecimal formatting with uppercase and alternate form.
    len = format_integer(buf, 16, FORMAT_FLAG_UPPER | FORMAT_FLAG_ALT, 255);
    buf[len] = '\0';
    printf("Hexadecimal: %s\n", buf); // Expected: "0XFF"

    // Test negative number formatting.
    len = format_integer(buf, 10, 0, -6789);
    buf[len] = '\0';
    printf("Negative Decimal: %s\n", buf); // Expected: "-6789"

    // Test unsigned formatting.
    len = format_integer(buf, 10, FORMAT_FLAG_UNSIGNED, -1);
    buf[len] = '\0';
    printf("Unsigned Decimal: %s\n", buf); // Expected: "18446744073709551615" (for uint64_t)

    return 0;
}