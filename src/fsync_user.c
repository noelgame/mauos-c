/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>
#include <syscall.h>

int fsync(int fd) {
    return syscall2(SYS_fsync, (uint32_t) fd);
}
