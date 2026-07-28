CC := gcc

CFLAGS := -Wall -Wextra -std=c23

GIT_HASH := $(shell git describe --always --dirty 2>/dev/null || echo "Not a git environment")


all:
	${CC} test.c -o test ${CFLAGS} -DLCH_GIT_HASH='"${GIT_HASH}"'
	./test


clang: CC := clang
clang: CFLAGS += -fblocks -lBlocksRuntime
clang: all


.PHONY: all clang
