/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Use builtin VA List support
 */

#pragma once

// Define the VA List type.
#define va_list __builtin_va_list

// Construct or Copy the VA List.
#define va_start(_ap, _last)  __builtin_va_start(_ap, _last)
#define va_copy(_src, _dst)   __builtin_va_copy(_src, _dst)

// End use of the VA List.
#define va_end(_ap)           __builtin_va_end(_ap)

// Access the VA list.
#define va_arg(_ap, _type)    __builtin_va_arg(_ap, _type)
