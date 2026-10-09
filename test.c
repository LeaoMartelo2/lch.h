#include <stdio.h>
#include <assert.h>

#define LCH_DISABLE_PREFIX
#define LCH_ENABLE_DEFER
//#define LCH_DISABLE_TODO
#define LCH_TYPEALIAS
#define LCH_IMPLEMENTATION
#include "lch.h"

typedef struct {
    i32 some_integer_context;
    f32 some_float_context;
    const char *some_cstr_context;
} my_on_crash_context;

void my_on_crash_function(void *context) {
    assert(context != NULL);
    my_on_crash_context *local_ctx = context;
    printf("my_on_crash_function: context = {%d, %f, %s}\n",
            local_ctx->some_integer_context,
            local_ctx->some_float_context,
            local_ctx->some_cstr_context);
    return;
}

int main(void) {

    i32 *ptr = malloc(sizeof(i32));

    defer {
        free(ptr);
        printf("freed'd ptr\n");
    };

    printf("%s\n", LCH_COMPILER_INFO);
    printf("%s\n", LCH_BUILD_DATE);
    printf("%s\n", LCH_GIT_HASH);

    todo("turn down for what", .dont_exit = true);


    lch_string_view string = sv("     @Hello, World!!!          ");
    lch_string_view comparision_string = sv("World");

    printf("string: |"sv_fmt "|\n", sv_arg(string));

    printf("Does string contain: |"sv_fmt"|? -> ", sv_arg(comparision_string));
    bool contains = sv_contains(string, comparision_string);
    printf("%s\n", bool_to_str_ex(contains, .all_caps = true));

    /*
    if(sv_contains(string, comparision_string)) {
        printf("true\n");
    }
    else {
        printf("false\n");
    }
    */

    sv_trim_left(&string);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    sv_trim_right(&string);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    sv_chop_left(&string, 1);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    sv_chop_right(&string, 2);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    sv_chop_by_delim(&string, ',');
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    sv_trim_left(&string);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    bool result = sv_equals(string, comparision_string);
    if(result) {
        printf("|"sv_fmt"| == |"sv_fmt"|\n", sv_arg(string), sv_arg(comparision_string));
    }
    else {
        printf("|"sv_fmt"| != |"sv_fmt"|\n", sv_arg(string), sv_arg(comparision_string));
    }

    sv_chop_right(&string, 1);
    printf("string: |"sv_fmt "|\n", sv_arg(string));

    result = sv_equals(string, comparision_string);
    if(result) {
        printf("|"sv_fmt"| == |"sv_fmt"|\n", sv_arg(string), sv_arg(comparision_string));
    }
    else {
        printf("|"sv_fmt"| != |"sv_fmt"|\n", sv_arg(string), sv_arg(comparision_string));
    }

    my_on_crash_context my_context = {
        .some_integer_context = 32767,
        .some_float_context = 1234.67f,
        .some_cstr_context = __func__
    };

#if 1

    crash(.title = "crash",
            .description = "this crashed because yes",
            /* .do_abrt = true, */
            ON_CRASH(my_on_crash_function),
            .callback_context = &my_context,
            .exit_code = 10);

#endif

#if 0
    quick_crash();
#endif

    return 0;
}

