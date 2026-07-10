# SPDX-FileCopyrightText: © 2026 Noel Allen
# SPDX-License-Identifier: CC BY-NC-4.0

$(warning "MWIDTH=$(MWIDTH)")
SOURCES += \
	mauos-c/src/assert.c \
	mauos-c/src/format.c \
	mauos-c/src/format_fractional.c \
	mauos-c/src/format_integer.c \
	mauos-c/src/memchr.c \
	mauos-c/src/memcmp.c \
	mauos-c/src/memcpy.c \
	mauos-c/src/memset.c \
	mauos-c/src/printf.c \
	mauos-c/src/putchar.c \
	mauos-c/src/puts.c \
	mauos-c/src/sprintf.c \
	mauos-c/src/strlen.c \
	mauos-c/src/strchr.c \
	mauos-c/src/strcmp.c \
	mauos-c/src/strcpy.c \
	mauos-c/src/strerror.c \
	mauos-c/src/strncpy.c


ifdef MAUOS_C_KERNEL
SOURCES += \
	mauos-c/src/exit_kernel.c \
	mauos-c/src/fsync_kernel.c

else
SOURCES += \
	mauos-c/src/exit_user.c \
	mauos-c/src/fsync_user.c \
	mauos-c/src/read_user.c \
	mauos-c/src/write_user.c \
	mauos-c/src/syscall_$(ARCH)_$(MWIDTH).c

endif

SYSTEMS += mauos-c/inc
SYSTEMS += mauos-c/inc/arch$(MWIDTH)
