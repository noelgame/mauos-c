/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Use builtin VA List support
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int (*ioctl)(driver_t *driver, int request, void *arg);
    int (*mmap)(driver_t *driver, void *buf, size_t count);
    int (*read)(driver_t *driver, void *buf, size_t count);
    int (*write)(driver_t *driver, const void *buf, size_t count);
} driver_t;