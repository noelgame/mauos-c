/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

void __noreturn __assert_builtin(const char *file, int line, const char *msg) {
    printf("ASSERT: %s(%d)\n\t%s\n", file, line, msg);
    fsync(1);
    abort();
}

void __weak_alias(__assert_builtin) assert_func(const char *file, int line, const char *msg);
