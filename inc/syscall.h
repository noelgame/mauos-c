/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <attributes.h>
#include <stddef.h>
#include <stdint.h>

__naked int syscall1(int snum);
__naked int syscall2(int snum, uint32_t arg1);
__naked int syscall3(int snum, uint32_t arg1, uint32_t arg2);
__naked int syscall4(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3);
__naked int syscall5(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
__naked int syscall6(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);
__naked int syscall7(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6);


#if defined(__x86_32__)
#define SYS_exit 1
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#define SYS_ioctl 54
#define SYS_mmap 90
#define SYS_munmap 91
#define SYS_fsync 118
#endif

#if defined(__x86_64__)
#define SYS_exit 60
#define SYS_read 0
#define SYS_write 1
#define SYS_open 2
#define SYS_close 3
#define SYS_ioctl 16
#define SYS_mmap 9
#define SYS_munmap 11
#define SYS_fsync 74
#endif
