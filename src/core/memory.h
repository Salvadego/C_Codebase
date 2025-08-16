#pragma once

#include "../base/base.h"

#ifdef __cplusplus
extern "C" {
#endif

// =============
// Configuration
// =============

// ===============
// Alignment Utils
// ===============

function inline u64 align_pow2(u64 value) {
        Assert((value & (value - 1)) == 0);
        return value;
}

function inline u64 align_up(u64 value, u64 alignment) {
        Assert(alignment && (alignment & (alignment - 1)) == 0);
        return (value + alignment - 1) & ~(alignment - 1);
}

// ===============
//  Heap wrappers
// ===============

void *mem_alloc(u64 size);
void *mem_alloc_zero(u64 size);
void *mem_realloc(void *ptr, u64 size);
void mem_free(void *ptr);

// ===============
// Arena Allocator
// ===============

typedef struct {
        u8 *base;
        u64 size;
        u64 offset;
} Arena;

typedef struct ArenaMaker {
        u64 offset;
} ArenaMarker;

Arena arena_create(u64 size);
Arena arena_from_buffer(void *buffer, u64 size);
void arena_destroy(Arena *arena);

void *arena_alloc(Arena *arena, u64 size, u64 alignment);
void *arena_push(Arena *arena, u64 size);
void *arena_push_zero(Arena *arena, u64 size, u64 alignment);

void arena_reset(Arena *arena);
ArenaMarker arena_mark(Arena *arena);
void arena_reset_to(Arena *arena, ArenaMarker marker);

// ===============
// Pool Allocator
// ===============

typedef struct Pool {
        u8 *base;
        u64 block_size;
        u64 capacity;
        u64 free_head;
} Pool;

#define POOL_NONE ((u64)~0ull)

Pool pool_create(u64 block_size, u64 capacity);
Pool pool_from_buffer(void *memory, u64 block_size, u64 capacity);
void pool_destroy(Pool *p);

void *pool_alloc(Pool *p);
void pool_free(Pool *p, void *ptr);

function inline void *arena_alloc_t(
    Arena *a, u64 count, u64 elem_size, u64 align) {
        u64 bytes = count * elem_size;
        return arena_alloc(a, bytes, align);
}

#ifdef __cplusplus
}
#endif
