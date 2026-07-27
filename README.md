lazy link:

```bash
wget https://raw.githubusercontent.com/LeaoMartelo2/lch.h/master/lch.h
```

git hash flag
```Makefile
GIT_HASH := $(shell git describe --always --dirty 2>/dev/null || echo "Not a git environment")
-DLCH_GIT_HASH='"${GIT_HASH}"'

```
