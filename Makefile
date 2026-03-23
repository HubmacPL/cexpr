CC = gcc
AR = ar
CFLAGS = -g -O2 -std=c11 -Wall -Wextra -Iinclude
ARFLAGS = rcs
LDFLAGS = -lm

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

LIB = libcexpr.a
TEST = calc_test

.PHONY: all clean

all: $(LIB) $(TEST)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST): main.c $(LIB)
	$(CC) $(CFLAGS) -o $@ main.c $(LIB) $(LDFLAGS)

clean:
	rm -f src/*.o $(LIB) $(TEST)
