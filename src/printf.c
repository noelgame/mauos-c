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


static int _dwrite(FormatProc_t *proc, const char *data, size_t len) {
    size_t count = min_uint32_t(len, proc->max_out - proc->cur_out);
    write((int) proc->data, data, count);
    return count;
}

int vdprintf(int fd, const char *fmt, va_list args) {
    FormatProc_t proc = {
        .write = _dwrite,
        .data = (void *) fd,
        .max_out = INT_MAX,
        .cur_out = 0,
    };

    return format_process(&proc, fmt, args);
}

int vprintf(const char *fmt, va_list args) {
    return vdprintf(1, fmt, args);    
}

int dprintf(int fd, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int print_size = vdprintf(fd, fmt, args);
    va_end(args);
    
    return print_size;
}

int fprintf(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int print_size = vdprintf((int) stream->fd, fmt, args);
    va_end(args);
    
    return print_size;
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int print_size = vdprintf(1, fmt, args);
    va_end(args);
    
    return print_size;
}