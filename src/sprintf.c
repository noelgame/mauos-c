/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <format.h>

#include <attributes.h>
#include <errno.h>
#include <limits.h>
#include <minmax.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

int _swrite(FormatProc_t *proc, const char *data, size_t len) {
    size_t count = min_uint32_t(len, proc->max_out - proc->cur_out);
    char *dst = (char *)proc->data + proc->cur_out;
    
    memcpy(dst, data, count);
    proc->cur_out += count;
    return count;
}

int vsnprintf(char *str, size_t size, const char *fmt, va_list args) {
    FormatProc_t proc = {
        .write = _swrite,
        .data = str,
        .max_out = size,
        .cur_out = 0,
    };

    int print_size = format_process(&proc, fmt, args);
    if (print_size < size) {
        str[print_size] = '\0';
    }
    return print_size;
}

int snprintf(char *str, size_t size, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int print_size = vsnprintf(str, size, fmt, args);
    va_end(args);
    
    return print_size;
}

int sprintf(char *str, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int print_size = vsnprintf(str, INT_MAX, fmt, args);
    va_end(args);
    
    return print_size;
}