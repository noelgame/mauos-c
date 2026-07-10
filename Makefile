MACHINE := host

include lib.mk
include ../mauos-build/base.mk

all: test-format test_numbers

CFLAGS = -isystem ./inc -Wall -Wextra -std=c11 -O0 -g -m32
DEFINES += MAUOS_C_USER=1

include lib.mk

OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))

$(BUILD_DIR)/%.o : $(REL_DIR)/%.c Makefile | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS)$(CFLAGS) $(HOST_CFLAGS) -c $< -o $@

.PHONY: libc.a
libc.a: $(BUILD_DIR)/libc.a

$(BUILD_DIR)/libc.a: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

.PHONY: info test-format

info:
	@echo "BUILD: $(BUILD_DIR)"
	@echo "REL_DIR: $(REL_DIR)"
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "HOST_CFLAGS: $(HOST_CFLAGS)"


$(BUILD_DIR)/format_harness: tests/format_harness.c src/format.c Makefile | $(BUILD)
	mkdir -p $(BUILD_DIR)
	$(HOSTCC) $(HOST_CFLAGS) tests/format_harness.c src/format.c -o $@

$(BUILD_DIR)/format_numbers: tests/format_numbers.c src/format.c src/format_integer.c src/format_fractional.c Makefile | $(BUILD)
	mkdir -p $(BUILD_DIR)
	$(HOSTCC) $(HOST_CFLAGS) tests/format_numbers.c src/format.c src/format_integer.c src/format_fractional.c -o $@

test-format: $(BUILD_DIR)/format_harness
	$<

test-numbers: $(BUILD_DIR)/format_numbers
	$<
