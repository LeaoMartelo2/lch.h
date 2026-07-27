GIT_HASH := $(shell git describe --always --dirty 2>/dev/null || echo "Not a git environment")

all:
	gcc test.c -o test -Wall -Wextra -DLCH_GIT_HASH='"${GIT_HASH}"'
	./test
