/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

#ifndef ERRNO_DEF
#define ERRNO_DEF(_err, _no, _desc)  [_err] = #_desc, 
#endif

static const char *_errors[ERROR_END] = {
    [0] = "Not an error",
#include <errno_def.h>
};

const char *strerror(errno_t num) {
    if ((num < 1) || (num >= ERROR_END)) {
        return NULL;
    }
    return _errors[num];
}