#include <stdio.h>

#define LCH_DISABLE_PREFIX
#define LCH_ENABLE_DEFER
#define LCH_DISABLE_TODO
#define LCH_TYPEALIAS
#define LCH_IMPLEMENTATION
#include "lch.h"

int main(void) {

    i32 *ptr = malloc(sizeof(i32));

    defer {
        free(ptr);
        printf("freed'd ptr\n");
    };

    printf("%s\n", LCH_COMPILER_INFO);
    printf("%s\n", LCH_BUILD_DATE);
    printf("%s\n", LCH_GIT_HASH);

    todo("turn down for what");


    lch_string_view string = sv("     @Hello, World!!!          ");
    printf("string: |"lch_sv_fmt "|\n", lch_sv_arg(string));

    sv_trim_left(&string);
    printf("string: |"lch_sv_fmt "|\n", lch_sv_arg(string));

    sv_trim_right(&string);
    printf("string: |"lch_sv_fmt "|\n", lch_sv_arg(string));

    sv_chop_left(&string, 1);
    printf("string: |"lch_sv_fmt "|\n", lch_sv_arg(string));

    sv_chop_right(&string, 2);
    printf("string: |"lch_sv_fmt "|\n", lch_sv_arg(string));









    crash(.title = "crash",
            .description = "this crashed because yes",
            .do_abrt = false,
            .exit_code = 10);

    return 0;
}
