/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

static func_t onexit = NULL;

void __weak __noreturn abort(void) {
    while(1);
}

void __weak _exit(int status) {
    (void) status;
    while(1);
}

void exit(int status) {
    if (onexit != NULL) {
        (*onexit)();
    }
    _exit(status);
}

errno_t atexit(func_t func) {
    if (onexit != NULL) {        
        onexit = func;
        return 0;
    }
    return -EBUSY;
}