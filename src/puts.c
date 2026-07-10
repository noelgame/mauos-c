/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <format.h>

#include <attributes.h>
#include <errno.h>
#include <string.h>

#include <stdarg.h>
#include <stdio.h>

int __weak puts(const char *str) {
    return dprintf(1, "%s\n", str);
}
