/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>
#include <syscall.h>

int mmap(void *buf, size_t len, int prot, int flags, int fd, off_t offset) {
    return syscall7(SYS_mmap, (uint32_t) buf, (uint32_t) len, (uint32_t) prot, (uint32_t) flags, (uint32_t) fd, (uint32_t) offset);
}

int munmap(void *buf, size_t len) {
    return syscall2(SYS_munmap, (uint32_t) buf, (uint32_t) len);
}
