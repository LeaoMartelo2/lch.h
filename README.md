# lch.h

collection of features i see myself implementing over and over again, on a common header for all my future projects, all on a single header library


### #define LCH_ENABLE_DEFER

This one requires GNU's extension for `cleanup` attribute, and `nested functions`, the second one being explicitly not supported by LLVM Clang
There is a work arround for it: Clang has `blocks` extensions from Apple. Though they're not ` 0 cost abstraction` on non-mac platforms
they require `-fblocks -lBlocksRuntime` (libdispatch, compiler-rt, libblocksruntime, why cant they all just have the same package name), that being a `minimal runtime to the program`

But its a small price if you think the executable stack from nested functions is a no-go in the situation.



lazy link:

```bash
wget https://raw.githubusercontent.com/LeaoMartelo2/lch.h/master/lch.h
```

git hash flag
```Makefile
GIT_HASH := $(shell git describe --always --dirty 2>/dev/null || echo "Not a git environment")
-DLCH_GIT_HASH='"${GIT_HASH}"'

```
