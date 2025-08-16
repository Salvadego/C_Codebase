#include <stdio.h>

#include "base/macros.h"
#include "core/memory.h"

#define MEMORY_USE_VM 0
#define CORE_IMPLEMENTATION
#include "core/core.h"

i32 main(void) {
        Allocator allocator = {
            .alloc = mem_alloc,
            .alloc_zero = mem_alloc_zero,
            .realloc = mem_realloc,
            .free = mem_free,
        };

        StringView sv = StringView_newFromChar("Hello, World!");
        char *result = StringView_toChar(allocator, sv);
        printf("%s\n", result);

        allocator.free(result);
        return 0;
}
