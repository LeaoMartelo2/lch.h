#include <stdio.h>

#define LCH_ENABLE_DEFER
#define LCH_TYPEALIAS
#define LCH_IMPLEMENTATION
#include "lch.h"

int main(void) {

    printf("%s\n", LCH_COMPILER_INFO);
    printf("%s\n", LCH_BUILD_DATE);
    printf("%s\n", LCH_GIT_HASH);



    lch_crash(.description = "crash",
            .detailed_description = "this crashed because yes",
            .exit_code = 185);

    return 0;
}
