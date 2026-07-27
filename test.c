#include <stdio.h>

#define LCH_ENABLE_DEFER
#define LCH_DISABLE_TODO
#define LCH_TYPEALIAS
#define LCH_IMPLEMENTATION
#include "lch.h"

int main(void) {

    printf("%s\n", LCH_COMPILER_INFO);
    printf("%s\n", LCH_BUILD_DATE);
    printf("%s\n", LCH_GIT_HASH);

    lch_todo("turn down for what");



    lch_crash(.description = "crash",
            .detailed_description = "this crashed because yes");

    return 0;
}
