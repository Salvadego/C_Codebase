#include <stdio.h>

#include "base/macros.h"
#include "base/types.h"
#include "core/array.h"

#define MEMORY_USE_VM 0
#define CORE_IMPLEMENTATION
#include "core/core.h"

DefineArrayType(u64, U64);

int main(void) {
        const u64 expected_count = 1e6;
        const u64 kilobytes = (expected_count * sizeof(u64)) / 1000;
        printf("Allocating %lu megabytes\n", kilobytes / 1000);
        Arena arena = arena_create(Kilobytes(kilobytes));

        U64Array a;
        U64ArrayInit(&a, &arena);

        for (u64 i = 0; i < expected_count; ++i) {
                U64ArrayPush(&a, i);
        }

        arena_destroy(&arena);
        return 0;
}
