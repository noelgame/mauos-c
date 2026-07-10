/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <attributes.h>

#define ASSERT_CRASH 0
#define ASSERT_LINE  1
#define ASSERT_FULL  2

#ifndef ASSERT_TYPE
#define ASSERT_TYPE ASSERT_FULL
#endif

#ifdef __assert_crash
#define __assert_crash  (((int*) 0) = 0)
#endif 

#ifdef ASSERT_ENABLED
#ifndef ASSERT_CRASH
# define assert(_e) ((_e) ? __noop : assert_func(__FILE__, __LINE__, #_e))
#else
# define assert(_e) ((_e) ? __noop : abort())
#endif
#endif

void __noreturn assert_func(const char *file, int line, const char *msg);
