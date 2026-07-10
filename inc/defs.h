/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define NULL ((void *) 0)

typedef signed long ptrdiff_t;

typedef signed long ssize_t;
typedef unsigned long size_t;

typedef signed long off_t;

typedef signed long intptr_t;
typedef unsigned long uintptr_t;

typedef void (*func_t)(void);


#define offsetof(_st, _mem) ((size_t) &(((_st *) 0)->_mem))
