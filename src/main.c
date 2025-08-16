#include <stdio.h>

#include "base/macros.h"
#include "core/memory.h"

#define MEMORY_USE_VM 0
#define CORE_IMPLEMENTATION
#include "core/core.h"

i32 main(void) {
        // ================================
        // Arena example
        // ================================
        Arena arena = arena_create(Kilobytes(1));  // 1 KB arena

        i32* numbers = (i32*)arena_push(&arena, 10 * sizeof(i32));
        for (int i = 0; i < 10; i++) {
                numbers[i] = i * i;
        }

        printf("Arena numbers:\n");
        for (i32 i = 0; i < 10; i++) {
                printf("%d ", numbers[i]);
        }
        printf("\n");

        // Reset arena → reuse memory
        arena_reset(&arena);
        char* msg = (char*)arena_push(&arena, 32);
        snprintf(msg, 32, "Hello from arena!");
        printf("%s\n", msg);

        arena_destroy(&arena);

        // ================================
        // Pool example
        // ================================
        Pool pool = pool_create(sizeof(i32), 4);  // 4 ints capacity

        i32* a = (i32*)pool_alloc(&pool);
        i32* b = (i32*)pool_alloc(&pool);
        i32* c = (i32*)pool_alloc(&pool);

        *a = 42;
        *b = 99;
        *c = -7;

        printf("Pool values: %d %d %d\n", *a, *b, *c);

        // Free back into pool
        pool_free(&pool, b);
        pool_free(&pool, a);
        pool_free(&pool, c);

        pool_destroy(&pool);

        // ================================
        // Heap wrappers
        // ================================
        char* buf = (char*)mem_alloc_zero(64);
        snprintf(buf, 64, "Heap allocated string");
        printf("%s\n", buf);
        mem_free(buf);

        return 0;
}
