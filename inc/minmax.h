/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define MIN_MAX(_ty) \
    const static inline _ty min_##_ty(_ty a, _ty b) { \
        return (a < b) ? a : b; \
    } \
    static inline _ty max_##_ty(_ty a, _ty b) { \
        return (a > b) ? a : b; \
    }

MIN_MAX(uint32_t);
MIN_MAX(int32_t);
MIN_MAX(uint64_t);
MIN_MAX(int64_t);
MIN_MAX(float);
MIN_MAX(double);

