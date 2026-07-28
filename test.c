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
    }

    printf("%s\n", LCH_COMPILER_INFO);
    printf("%s\n", LCH_BUILD_DATE);
    printf("%s\n", LCH_GIT_HASH);

    todo("turn down for what");


/*
    crash(.description = "crash",
            .detailed_description = "this crashed because yes");
*/

    return 0;
}
