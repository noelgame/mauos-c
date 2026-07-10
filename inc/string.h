/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

// Length and Set
void *memset(void *dst, int c, size_t n);
size_t strlen(const char *s);

// Find
char *strchr(const void *src, int val, size_t n);

// Compare
int memcmp(const void *srcA, const void *srcB, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

// Copy
void *memcpy(void *dst, const void *src, size_t n);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
