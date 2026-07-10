/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>
#include <syscall.h>

int read(int fd, void *buf, size_t count) {
    return syscall4(SYS_read, (uint32_t) fd, (uint32_t) buf, (uint32_t) count);
}