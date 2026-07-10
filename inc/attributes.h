/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define __aligned(_a)       __attribute__((alligned(_a)))
#define __fallthrough       __attribute__((fallthrough))
#define __noinline          __attribute__((noinline))
#define __noreturn          __attribute__((noreturn))
#define __packed            __attribute__((packed))
#define __section(_s)       __attribute__((section(#_s)))
#define __used              __attribute__((used))
#define __unused            __attribute__((unused))
#define __naked             __attribute__((naked))
#define __weak              __attribute__((weak))
#define __weak_alias(_a)    __attribute__((weak, alias(#_a)))

#define __init              __section(".text.init") __noinline
#define __noop              (void)0

typedef void (*func_t)(void);