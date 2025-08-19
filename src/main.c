#include <stdio.h>

#define MEMORY_USE_VM 0
#define CORE_IMPLEMENTATION
#include "core/core.h"

int main(void) {
        StringView sv = StringView_newFromChar("   Hello, World!   ");

        printf("Original: ");
        StringView_print(sv);

        StringView trimmed = StringView_trimWhitespace(sv);
        printf("Trimmed: ");
        StringView_print(trimmed);

        StringView copy = sv;
        StringView_trimWhitespaceInPlace(&copy);
        printf("Trimmed in-place: ");
        StringView_print(copy);

        StringView chopped = StringView_chopByDelimiter(&copy, ',');
        printf("Chopped head: ");
        StringView_print(chopped);
        printf("Remaining: ");
        StringView_print(copy);

        return 0;
}
