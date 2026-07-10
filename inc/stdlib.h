/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <errno.h>
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1


// Setup one function to be called on exit.
errno_t atexit(func_t func);

// Abort, can be overridden.
void __noreturn abort(void);

// Exit with a value, can be overridden.
// Calls _exit after trigging atexit function.
void __noreturn exit(int val);

// Just loops, can be overriden.
void __noreturn _exit(int val);
