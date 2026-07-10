/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>
#include <syscall.h>

int write(int fd, const void *buf, size_t count) {
    return syscall4(SYS_write, (uint32_t) fd, (uint32_t) buf, (uint32_t) count);
}
