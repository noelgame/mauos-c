/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

int mmap(int fd, void *buf, size_t count) {
    return syscall3(SYSCALL_MMAP, (uint32_t) fd, (uint32_t) buf, (uint32_t) count);
}
