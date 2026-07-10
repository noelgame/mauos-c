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

#define ASSERT_EQ(_a, _b)                                                                           \
    do {                                                                                           \
        long long _aa = (long long)(_a);                                                           \
        long long _bb = (long long)(_b);                                                           \
        if (_aa != _bb) {                                                                          \
            fprintf(stderr, "%s:%d: ASSERT_EQ failed: %s (%lld) != %s (%lld)\n", __FILE__, __LINE__, \
                    #_a, _aa, #_b, _bb);                                                           \
            return 1;                                                                              \
        }                                                                                          \
    } while (0)

static int test_format_flags(void) {
    uint8_t f;

    f = 0;
    ASSERT_EQ(format_flags("", &f), 0);
    ASSERT_EQ((unsigned)f, 0u);

    f = 0;
    ASSERT_EQ(format_flags("-+#0 ", &f), 5);
    ASSERT_EQ((unsigned)f,
              (unsigned)(FORMAT_FLAG_MINUS | FORMAT_FLAG_PLUS | FORMAT_FLAG_ALT | FORMAT_FLAG_ZERO |
                         FORMAT_FLAG_SPACE));

    f = 0;
    ASSERT_EQ(format_flags("-+5", &f), 2);
    ASSERT_EQ((unsigned)f, (unsigned)(FORMAT_FLAG_MINUS | FORMAT_FLAG_PLUS));

    f = 0;
    ASSERT_EQ(format_flags("00-", &f), 3);
    ASSERT_EQ((unsigned)f, (unsigned)(FORMAT_FLAG_ZERO | FORMAT_FLAG_MINUS));

    return 0;
}

static int test_format_width(void) {
    int w;

    w = 0;
    ASSERT_EQ(format_width("*", &w), 1);
    ASSERT_EQ(w, -1);

    w = 0;
    ASSERT_EQ(format_width("012", &w), 3);
    ASSERT_EQ(w, 12);

    w = 99;
    ASSERT_EQ(format_width("x", &w), 0);

    w = 0;
    ASSERT_EQ(format_width("", &w), 0);

    return 0;
}

static int test_format_size(void) {
    FormatSize_t s;

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("", &s), 0);
    ASSERT_EQ(s, FORMAT_SIZE_NONE);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("hh", &s), 2);
    ASSERT_EQ(s, FORMAT_SIZE_HH);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("ll", &s), 2);
    ASSERT_EQ(s, FORMAT_SIZE_LL);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("j", &s), 1);
    ASSERT_EQ(s, FORMAT_SIZE_J);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("z", &s), 1);
    ASSERT_EQ(s, FORMAT_SIZE_Z);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("t", &s), 1);
    ASSERT_EQ(s, FORMAT_SIZE_T);

    s = FORMAT_SIZE_NONE;
    ASSERT_EQ(format_size("L", &s), 1);
    ASSERT_EQ(s, FORMAT_SIZE_L_UPPER);

    return 0;
}

static int test_format_convertion(void) {
    FormatConv_t c;
    int n;

    n = format_convertion(NULL, &c);
    ASSERT_EQ(n, -(int)EINVAL);

    n = format_convertion("", &c);
    ASSERT_EQ(n, -(int)EINVAL);

    n = format_convertion("%", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, '%');

    n = format_convertion("*lld", &c);
    ASSERT_EQ(n, 4);
    ASSERT_EQ(c.width_present, true);
    ASSERT_EQ(c.width, -1);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ(c.size, FORMAT_SIZE_LL);
    ASSERT_EQ(c.precision_present, false);
    ASSERT_EQ((int)c.base, 10);

    n = format_convertion("-5d", &c);
    ASSERT_EQ(n, 3);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ((unsigned)c.flags, (unsigned)FORMAT_FLAG_MINUS);
    ASSERT_EQ(c.width_present, true);
    ASSERT_EQ(c.width, 5);
    ASSERT_EQ((int)c.base, 10);

    n = format_convertion("10u", &c);
    ASSERT_EQ(n, 3);
    ASSERT_EQ((unsigned)c.flags, (unsigned)FORMAT_FLAG_UNSIGNED);
    ASSERT_EQ(c.width_present, true);
    ASSERT_EQ(c.width, 10);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ(c.size, FORMAT_SIZE_NONE);
    ASSERT_EQ(c.precision_present, false);

    n = format_convertion("+10ld", &c);
    ASSERT_EQ(n, 5);
    ASSERT_EQ(c.width_present, true);
    ASSERT_EQ(c.width, 10);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ(c.size, FORMAT_SIZE_L);
    ASSERT_EQ(c.precision_present, false);

    n = format_convertion("+.6f", &c);
    ASSERT_EQ(n, 4);
    ASSERT_EQ(c.width_present, false);
    ASSERT_EQ(c.precision_present, true);
    ASSERT_EQ(c.precision, 6);
    ASSERT_EQ(c.conversion, 'f');
    ASSERT_EQ(c.size, FORMAT_SIZE_NONE);

    n = format_convertion("+10.6f", &c);
    ASSERT_EQ(n, 6);
    ASSERT_EQ((unsigned)c.flags, (unsigned)FORMAT_FLAG_PLUS);
    ASSERT_EQ(c.width_present, true);
    ASSERT_EQ(c.width, 10);
    ASSERT_EQ(c.precision_present, true);
    ASSERT_EQ(c.precision, 6);
    ASSERT_EQ(c.conversion, 'f');
    ASSERT_EQ(c.size, FORMAT_SIZE_NONE);

    n = format_convertion(".f", &c);
    ASSERT_EQ(n, 2);
    ASSERT_EQ(c.precision_present, true);
    ASSERT_EQ(c.precision, 0);
    ASSERT_EQ(c.conversion, 'f');

    n = format_convertion("jd", &c);
    ASSERT_EQ(n, 2);
    ASSERT_EQ(c.size, FORMAT_SIZE_J);
    ASSERT_EQ(c.conversion, 'd');

    n = format_convertion("x", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ((int)c.base, 16);
    ASSERT_EQ((unsigned)c.flags & (unsigned)FORMAT_FLAG_UPPER, 0u);

    n = format_convertion("X", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ((int)c.base, 16);
    ASSERT_EQ((unsigned)c.flags & (unsigned)FORMAT_FLAG_UPPER, (unsigned)FORMAT_FLAG_UPPER);

    n = format_convertion("p", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ((int)c.base, 16);

    n = format_convertion("#5x", &c);
    ASSERT_EQ(n, 3);
    ASSERT_EQ((unsigned)c.flags & (unsigned)FORMAT_FLAG_ALT, (unsigned)FORMAT_FLAG_ALT);
    ASSERT_EQ(c.width, 5);
    ASSERT_EQ(c.conversion, 'd');
    ASSERT_EQ((int)c.base, 16);

    n = format_convertion("E", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'f');
    ASSERT_EQ((unsigned)c.flags & (unsigned)FORMAT_FLAG_UPPER, (unsigned)FORMAT_FLAG_UPPER);

    n = format_convertion("g", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'f');

    n = format_convertion("c", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 'c');

    n = format_convertion("s", &c);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(c.conversion, 's');

    n = format_convertion("o", &c);
    ASSERT_EQ(n, -(int)EILSEQ);

    n = format_convertion("q", &c);
    ASSERT_EQ(n, -(int)EILSEQ);

    n = format_convertion("+10ll", &c);
    ASSERT_EQ(n, -(int)EILSEQ);

    n = format_convertion("-%", &c);
    ASSERT_EQ(n, -(int)EILSEQ);

    return 0;
}

int main(void) {
    if (test_format_flags() != 0) {
        return 1;
    }
    if (test_format_width() != 0) {
        return 1;
    }
    if (test_format_size() != 0) {
        return 1;
    }
    if (test_format_convertion() != 0) {
        return 1;
    }

    puts("format_harness: all tests passed");
    return 0;
}
