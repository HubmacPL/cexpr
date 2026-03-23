
CC = gcc
AR = ar
CFLAGS = -g -O2 -std=c11 -Wall -Wextra -Iinclude
ARFLAGS = rcs
LDFLAGS = -lm

# python3-config detection and flags (computed at make parse time)
PY3_CONFIG := $(shell command -v python3-config 2>/dev/null)
ifeq ($(PY3_CONFIG),)
PY_CFLAGS :=
PY_LDFLAGS :=
else
PY_CFLAGS := $(shell python3-config --cflags)
PY_LDFLAGS := $(shell python3-config --ldflags)
endif

SRCS = $(wildcard src/*.c)
BUILD_DIR = build
OBJS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

LIB = $(BUILD_DIR)/libcexpr.a
TEST = $(BUILD_DIR)/calc_test

.PHONY: all clean

all: $(LIB) $(TEST)

# build shared library for Python bindings
.PHONY: shared
shared: CFLAGS += -fPIC
shared: $(BUILD_DIR)
	$(CC) $(CFLAGS) -shared src/*.c -Iinclude -lm -o $(BUILD_DIR)/libcexpr.so

# Build CPython extension module (requires python3-config)
.PHONY: pyext
pyext: $(LIB)
	@if [ -z "$(PY3_CONFIG)" ]; then \
		echo "python3-config not found. Install Python development headers (e.g. python3-dev) and ensure python3-config is in PATH."; \
		exit 1; \
	fi
	$(CC) -fPIC -shared $(CFLAGS) $(PY_CFLAGS) python-binding/cexprmodule.c $(LIB) -o python-binding/cexpr.so $(PY_LDFLAGS) -lm

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST): main.c $(LIB)
	$(CC) $(CFLAGS) -o $@ main.c $(LIB) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

