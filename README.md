# lch.h

A collection of features i see myself implementing over and over again, on a common header for my future projects

quick link:

```bash
wget https://raw.githubusercontent.com/LeaoMartelo2/lch.h/master/lch.h
```

### LCH_GIT_HASH
```Makefile
GIT_HASH := $(shell git describe --always --dirty 2>/dev/null || echo "Not a git environment")
-DLCH_GIT_HASH='"${GIT_HASH}"'

```

Defaults to `"Not in a Git environment"` if not defined.


### #define LCH_ENABLE_DEFER

Enable the usage of a makeshift `defer` keyword (as proposed in C29) with the heavy use of macros.
Sadly this is compiler dependant, so its only recomended to be used in specific environments.

This requires GNU's extension for `cleanup` attribute, and `nested functions`, the second one being explicitly not supported by LLVM/Clang.

There is a work arround for it: Clang has `blocks` extensions from Apple (objective-c). Though they're not ` 0 cost abstraction` on non-macOS platforms.
They require compiling with `-fblocks -lBlocksRuntime` 
(Providers for that package might have a different name depending on the distributor, common names are: `libdispatch`, `compiler-rt`, `libblocksruntime`, or included in objective-c tooling), that being a `minimal runtime to the program`.

The Clang approach is preferrable if you believe the risks associated with nested functions in GCC (that creates a executable stack) are not worth it.

If using with Clang, the defer block explicitly needs a semi-colon (`;`) at the end of the block:
```c

int foo = malloc(sizeof(int));

defer {
    free(foo);
}; /* <--- HERE */

```

That is not needed on the GCC approach, but C is not picky about empty statements.

Macro and GNU extension based Defer implementation based on [cmhood/c-defer](https://github.com/cmhood/c-defer/blob/master/defer.h)



### lch_crash

Helper function to allow you to generate good/useful crash messages. 
This is one of the most complex funtions argument wise, but its functionality its stupidly simple.

All of the arguments are optional, therefore they must be named during call time, check usage example bellow.


```c

/* OPTIONALLY define a function to be called uppon call (on_crash() callback) 
   Its passed through a opaque pointer (void *), so for convenience, a type can be defined.
*/

typedef struct {
    size_t my_context_value;
} my_on_crash_context;

/* function signature MUST only accept a void * */
void my_on_crash_function(void *context) {
    my_on_crash_context *local_ctx = context; /* correctly interprets the context */
    printf("context recieved: %zu\n", local_ctx->my_context_value);
}

/* OPTIONALLY define where ethe crash log is sent to */

FILE *my_file_handle = fopen("crash_log.txt", "a");

my_on_crash_context context = { .my_context_value = 32767; };

lch_crash(
    .title = "Program has crashed.", /* <- Define a title for your crash message */
    .description = "Some info about the crash", /* <- Give some small description about the crash */
    .detailed_description = "Some more info", /* <- Self explanatory */
    .exit_code = 1, /* <- Defines the exit code for the program */
    .file_write_to = my_file_handle, /* <- Pointer to FILE handle, defaults to stderr */
    .do_abrt = false, /* <- uses abort() instead of exit(), ignores .exit_code */
    ON_CRASH(my_on_crash_function), /* <- THIS one does not require . at the start */
    .callback_context = &my_context);

```

There is also a `lch_quick_crash()` macro, that gives a pre-made crash message:

lch_quick_crash() parameters:
```
.title = "Program has crashed"
.description = "No additional information has been provided"
.exit_code = 1
```

It also includes identification of where the crash occured:

At: FILE_NAME:LINE_NUMBER, in function FUNCTION_NAME()


### lch_todo()

Display a quick todo message, where the message was called, and exits the program with abort()

Optionally, having `.dont_exit` set to true, just makes it return after printing the TODO information. Useful for testing unimplemented functions.


Example:
```c

float my_unfinished_function(int a) {
    lch_todo("Implement this function", .dont_exit = true);
    /* we havent implemented this function yet, but we can use .dont_exit to simulate a valid return without implementing it yet */
    return 1234.5678f;

}
```


Adding `#define LCH_DISABLE_TODO` removes all todo messages / exits.


### LCH_COMPILER_INFO

A C-string containing the name and version of the compiler used to build the executable.
Printed in the following format:

`"COMPILERNAME [COMPILER_VERSION]"`

List of supported compilers
- GCC
- Clang

If the used compiler is not on the list, instead will return the string `"Unknown Compiler"`


### LCH_BUILD_DATE

Returns a string containing time of build

Example:

`Built at Oct 9 2026 at 08:38:50`

###

### LCH_TYPEALIAS

Enables small grouping of `typedef` aliases to ease the use of precise types: 

```c
    typedef int8_t   i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;

    typedef float f32;
    typedef double f64;
    
    typedef uint8_t   u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
``` 










