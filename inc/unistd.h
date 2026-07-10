/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

ssize_t read(int fd, const void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);