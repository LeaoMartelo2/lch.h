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
    lch_string_view comparision_string = sv("World");

    printf("string: |"sv_fmt "|\n", sv_arg(string));

    printf("Does string contain: |"sv_fmt"|? -> ", sv_arg(comparision_string));
    if(sv_contains(string, comparision_string)) {
        printf("true\n");
    }
    else {
        printf("false\n");
    }

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





    crash(.title = "crash",
            .description = "this crashed because yes",
            .do_abrt = false,
            .exit_code = 10);

    return 0;
}
