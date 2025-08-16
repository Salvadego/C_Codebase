#include <stdio.h>

#define CORE_IMPLEMENTATION
#include "core/core.h"

i32 main(void) {
        // ================================
        // Arena example
        // ================================
        Arena arena = arena_create(1024);  // 1 KB arena

        int* numbers = (int*)arena_push(&arena, 10 * sizeof(int));
        for (int i = 0; i < 10; i++) {
                numbers[i] = i * i;
        }

        printf("Arena numbers:\n");
        for (int i = 0; i < 10; i++) {
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
        Pool pool = pool_create(sizeof(int), 4);  // 4 ints capacity

        int* a = (int*)pool_alloc(&pool);
        int* b = (int*)pool_alloc(&pool);
        int* c = (int*)pool_alloc(&pool);

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
