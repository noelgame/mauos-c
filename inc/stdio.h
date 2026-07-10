/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>


#define EOF (-1)

struct __FILE {
    int fd;
};

typedef struct __FILE  FILE;


extern FILE _STDIN;
extern FILE _STDOUT;
extern FILE _STDERR;

#define stdin (&_STDIN)
#define stdout (&_STDOUT)
#define stderr (&_STDERR)

int putchar(int c);
int puts(const char *str);

int printf(const char *fmt, ...);
int dprintf(int fd, const char *fmt, ...);
int fprintf(FILE *stream, const char *fmt, ...);

int vprintf(const char *fmt, va_list args);
int vdprintf(int fd, const char *fmt, va_list args);

int sprintf(char *str, const char *fmt, ...);
int snprintf(char *str, size_t max, const char *fmt, ...);
int vsnprintf(char *str, size_t max, const char *fmt, va_list args);

int read(int fd, void *buf, size_t count);
int write(int fd, const void *buf, size_t count);
int close(int fd);
int fsync(int fd);

