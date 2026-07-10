/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifndef ERRNO_DEF
#define ERRNO_DEF(_err, _no, _desc)  _err = _no,
#endif

typedef enum errno_t {
#include <errno_def.h>
    ERROR_END
} errno_t;

#undef ERRNO_DEF