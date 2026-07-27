#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>

#ifndef LCH_H
#define LCH_H

#ifndef LCH_API
    #define LCH_API
#endif

#if defined(__GNUC__)
    #define LCH_COMPILER_INFO "GCC [" __VERSION__ "]"
#elif defined(__clang__)
    #define LCH_COMPILER_INFO "Clang [" __clang_version__ "]"
#else
    #define LCH_COMPILER_INFO "Unknown compiler"
#endif

#ifndef LCH_BUILD_DATE
    #define LCH_BUILD_DATE "Built at " __DATE__ " at " __TIME__ ""
#endif

#ifndef LCH_GIT_HASH
    #define LCH_GIT_HASH "Not in a Git environment (or not defined at build time)"
#endif



#define UNUSED(x) ((void)(x))
#define BOOL_TO_STR(x) ((x) ? "true" : "false")


#ifdef LCH_TYPEALIAS
    typedef int32_t i32;
    typedef uint32_t u32;
    typedef int64_t i64;
    typedef uint64_t u64;
    typedef float f32;
    typedef double f64;
#endif /* LCH_TYPEALIAS */



#ifdef LCH_ENABLE_DEFER
    #if !defined(__GNUC__) || defined(__clang__)
        #error "LCH_ENABLE_DEFER error: The 'defer' macro requires GNU nested functions extension, that are not supported by Clang or similar."
    #endif

    /* Macro and GNU extension based Defer implementation based on: */
    /* https://github.com/cmhood/c-defer/blob/master/defer.h        ->       Unlicense */
    #define defer defer__2(__COUNTER__)
    #define defer__2(X) defer__3(X)
    #define defer__3(X) defer__4(defer__id##X)
    #define defer__4(ID) auto void ID##func(char (*)[]); __attribute__((cleanup(ID##func), unused)) char ID##var[0]; void ID##func(__attribute__((unused)) char (*ID##param)[])
    /* Sligtly modified to remove some warnings */
#endif /* LCH_ENABLE_DEFER */



#ifndef LCH_MAX_TF_BUF
    #define LCH_MAX_TF_BUF 4
#endif
#ifndef LCH_TB_LEN
    #define LCH_TB_LEN 1024
#endif
LCH_API const char *lch_textformat(const char *fmt, ...);



typedef struct {
    const char *description;
    const char *detailed_description;
    const char *title;
    const size_t line_where;
    const char *file_where;
    const char *function_where;
    const short exit_code;
    FILE *const file_write_to;
} lch_crash_details;

#ifndef LCH_CRASH_FD
    #define LCH_CRASH_FD stderr
#endif

[[noreturn]] LCH_API void lch_crash_opt(lch_crash_details details);

#define lch_crash(...) lch_crash_opt((lch_crash_details){.file_where = __FILE__,\
        .line_where = __LINE__,\
        .function_where = __func__,\
        __VA_ARGS__})



typedef struct {
    const char *file_where;
    const size_t line_where;
    const char *function_where;
} lch_todo_details;

[[noreturn]] LCH_API void lch_todo_opt(lch_todo_details details, const char *txt);

#ifndef LCH_DISABLE_TODO

    #define lch_todo(txt) lch_todo_opt((lch_todo_details){.file_where = __FILE__,\
            .line_where = __LINE__,\
            .function_where = __func__}, (txt))
#endif

#ifdef LCH_DISABLE_TODO
    #define lch_todo(txt) 
#endif



#ifdef LCH_DISABLE_PREFIX
    #define textformat lch_textformat
    #define crash lch_crash
    #define todo lch_todo
#endif



#endif /* LCH_H */

#ifdef LCH_IMPLEMENTATION

LCH_API const char *lch_textformat(const char *fmt, ...) {
    static char buffers[LCH_MAX_TF_BUF][LCH_TB_LEN];
    static size_t index = 0;

    char *current_buffer = buffers[index];
    memset(current_buffer, 0, LCH_TB_LEN);

    va_list args;
    va_start(args, fmt);
    size_t required_sz = vsnprintf(current_buffer, LCH_TB_LEN, fmt, args);
    va_end(args);

    if(required_sz >= LCH_TB_LEN) {
        fprintf(stderr, "[LCH] String formating fail: attempting to format string larger than LCH_TB_LEN\n");
        return nullptr;
    }

    index += 1;

    if(index >= LCH_MAX_TF_BUF) index = 0;

    return current_buffer;
}

[[noreturn]] LCH_API void lch_crash_opt(lch_crash_details details) {

    FILE *write_handle = {};

    if(details.file_write_to) {
        write_handle = details.file_write_to;
    }
    else {
        write_handle = LCH_CRASH_FD;
    }

    fprintf(write_handle, "\n\n");

    if(details.title) fprintf(write_handle, "%s\n", details.title);
    if(details.description) fprintf(write_handle, "%s\n", details.description);
    if(details.detailed_description) fprintf(write_handle, "%s\n", details.detailed_description);

    if(details.file_where && details.function_where && details.line_where) {
        fprintf(write_handle, "At: %s:%zu, in function %s()\n",
                details.file_where, details.line_where, details.function_where);
    }

    fflush(write_handle);
    exit(details.exit_code);
    /*   ^  0 by default */
}


[[noreturn]] LCH_API void lch_todo_opt(lch_todo_details details, const char *txt) {

    if(txt) printf("TODO: %s\n", txt);

    if(details.file_where && details.function_where && details.line_where) {
        printf("At: %s:%zu, in function %s()\n",
            details.file_where, details.line_where, details.function_where);
    }

    fflush(stdout);
    abort();
}

#endif /* LCH_IMPLEMENTATION */
