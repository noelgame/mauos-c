/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <mauos-c.h>

int write(int fd, const void *buf, size_t count) {
    driver_t *driver = get_driver(fd);
    assert(driver != NULL);
    assert(buf != NULL);
    assert(count > 0);

    return driver->write(driver, buf, count);
}