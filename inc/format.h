/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum FormatFlags_t {
    FORMAT_FLAG_MINUS = 1u << 0,
    FORMAT_FLAG_PLUS = 1u << 1,
    FORMAT_FLAG_SPACE = 1u << 2,
    FORMAT_FLAG_ALT = 1u << 3,
    FORMAT_FLAG_ZERO = 1u << 4,
    FORMAT_FLAG_UPPER = 1u << 5,
    FORMAT_FLAG_UNSIGNED = 1u << 6,
} FormatFlags_t;

typedef enum FormatSize_t {
    FORMAT_SIZE_NONE = 0,
    FORMAT_SIZE_HH,
    FORMAT_SIZE_H,
    FORMAT_SIZE_L,
    FORMAT_SIZE_LL,
    FORMAT_SIZE_L_UPPER,
    FORMAT_SIZE_J,
    FORMAT_SIZE_Z,
    FORMAT_SIZE_T,
} FormatSize_t;

typedef struct {
    uint8_t flags;
    uint8_t base;
    bool width_present;
    bool precision_present;
    char conversion;
    int width;
    int precision;
    FormatSize_t size;
} FormatConv_t;

struct FormatProc_s;
typedef struct FormatProc_s FormatProc_t;

struct FormatProc_s {
    int (*write)(FormatProc_t *proc, const char *data, size_t len);
    char tmp_buf[32];
    int cur_out;
    int max_out;
    void *data;
};

int format_flags(const char *fmt, uint8_t *flags);
int format_width(const char *fmt, int *pwidth);
int format_size(const char *fmt, FormatSize_t *psize);


/**
 * Fill tmp_buff in FormatConv_t based on the conversion specification.
 *
 * @param dst   Points at the buffer to write the formatted number to.
 * @param base  The base of the number to format.
 * @param flags The format flags.
 * @param num   The number to format.
 * @return Bytes written on success, or a negative errno (-EINVAL, -EILSEQ).
 */
int format_integer(char *dst, int base, uint8_t flags, int64_t num);

/**
 * Fill tmp_buff in FormatConv_t based on the conversion specification.
 *
 * @param dst   Points at the buffer to write the formatted number to.
 * @param flags The format flags.
 * @param num   The number to format.
 * @return Bytes written on success, or a negative errno (-EINVAL, -EILSEQ).
 */
int format_fractional(char *dst, uint8_t flags, double num);

/**
 * Parse one printf conversion after the leading '%'.
 *
 * @param fmt   Points at the first character after '%'.
 * @param out   Filled on success.
 * @return Bytes consumed on success, or a negative errno (-EINVAL, -EILSEQ).
 */
int format_convertion(const char *fmt, FormatConv_t *out);

/**
 * Process a format string and arguments, calling the provided functions to print the output.
 *
 * @param proc  Points at the processing object, used to output.
 * @param fmt   Points at the first character after '%'.
 * @param args  List of arguments to be used for the format conversions.
 * @return Number of output characters, or a negative errno (-EINVAL, -EILSEQ).
 */
int format_process(FormatProc_t *proc, const char *fmt, va_list args);
