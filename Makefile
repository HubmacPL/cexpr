
CC = gcc
AR = ar
CFLAGS = -g -O2 -std=c11 -Wall -Wextra -Iinclude
ARFLAGS = rcs
LDFLAGS = -lm

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

