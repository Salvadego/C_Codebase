#include "memory.h"

#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef union {
        void* p;
        long double ld;
        long long ll;
} max_align_t;

typedef struct MemRegion {
        u8* ptr;
        u64 size;
        i32 owns;
} MemRegion;

#define ARENA_DEFAULT_ALIGNMENT    \
        (offsetof(                 \
            struct {               \
                    char c;        \
                    max_align_t t; \
            },                     \
            t))

static MemRegion region_acquire(u64 size) {
        MemRegion r = {0};
#if MEMORY_USE_VM
        // Windows
#        if BASE_OS_WINDOWS
        void* p = VirtualAlloc(
            NULL,
            (SIZE_T)size,
            MEM_RESERVE | MEM_COMMIT,
            PAGE_READWRITE);
        if (p) {
                r.ptr = p;
                r.size = size;
                r.owns = 1;
        }
#        elif BASE_OS_LINUX || BASE_OS_MACOS || BASE_OS_FREEBSD ||  \
            BASE_OS_NETBSD || BASE_OS_OPENBSD || BASE_OS_ILLUMOS || \
            BASE_OS_UNIX
        void* p = mmap(
            NULL,
            (size_t)size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,
            0);
        if (p != MAP_FAILED) {
                r.ptr = p;
                r.size = size;
                r.owns = 1;
        }
#        else
        // Fallback
        void* p = malloc((size_t)size);
        if (p) {
                r.ptr = p;
                r.size = size;
                r.owns = 1;
        }
#        endif
#else
        void* p = malloc((size_t)size);
        if (p) {
                r.ptr = p;
                r.size = size;
                r.owns = 1;
        }
#endif
        return r;
}

// Heap Wrappers

void* mem_alloc(u64 size) {
        if (!size) return null;
        void* p = malloc((size_t)size);
        Assert(p != null || size == 0);
        return p;
}
void* mem_alloc_zero(u64 size) {
        void* p = mem_alloc(size);
        if (p) MemoryZero(p, (size_t)size);
        return p;
}
void* mem_realloc(void* ptr, u64 new_size) {
        void* p = realloc(ptr, (size_t)new_size);
        Assert(p != null || new_size == 0);
        return p;
}
void mem_free(void* ptr) {
        free(ptr);
}

// Arena Allocator

Arena arena_create(u64 size) {
        Arena a = {0};
        if (!size) return a;
        MemRegion r = region_acquire(size);
        if (!r.ptr) return a;
        a.base = (u8*)r.ptr;
        a.size = r.size;
        a.offset = 0;
        return a;
}

Arena arena_from_buffer(void* memory, u64 size) {
        Arena a = {0};
        a.base = (u8*)memory;
        a.size = size;
        a.offset = 0;
        return a;
}

void arena_destroy(Arena* arena) {
        if (!arena || !arena->base) return;
#if BASE_OS_WINDOWS
        VirtualFree(arena->base, 0, MEM_RELEASE);
#elif BASE_OS_LINUX || BASE_OS_MACOS
        munmap(arena->base, arena->size);
#else
        free(arena->base);
#endif
        arena->base = NULL;
        arena->size = 0;
        arena->offset = 0;
}

void* arena_alloc(Arena* a, u64 size, u64 align) {
        Assert(a && a->base);
        size_t alignment = align ? align : ARENA_DEFAULT_ALIGNMENT;
        u64 cur = (u64)a->offset;
        size_t aligned = align_up(cur, alignment);
        u64 end = aligned + size;
        if (end > a->size) return null;
        a->offset = end;
        return a->base + aligned;
}

void* arena_push(Arena* a, u64 size) {
        u64 align = ARENA_DEFAULT_ALIGNMENT;
        return arena_alloc(a, size, align);
}

void* arena_push_zero(Arena* a, u64 size, u64 align) {
        void* p = arena_alloc(a, size, align);
        if (p) MemoryZero(p, (size_t)size);
        return p;
}

void arena_reset(Arena* a) {
        Assert(a && a->base);
        a->offset = 0;
}

ArenaMarker arena_mark(Arena* a) {
        Assert(a && a->base);
        ArenaMarker m = {a->offset};
        return m;
}

void arena_reset_to(Arena* a, ArenaMarker marker) {
        Assert(a && a->base);
        a->offset = marker.offset;
}

//==================================================
// Pool (fixed-size)
//==================================================
function u64 pool_round_block(u64 b) {
        u64 m = (u64)AlignOfType(void*);
        if (b < sizeof(void*)) b = sizeof(void*);
        return align_up(b, m);
}

Pool pool_create(u64 block_size, u64 capacity) {
        Pool p = {0};
        if (capacity == 0) return p;
        block_size = pool_round_block(block_size);

        u64 total = block_size * capacity;
        MemRegion r = region_acquire(total);
        if (!r.ptr) return p;

        p.base = (u8*)r.ptr;
        p.block_size = block_size;
        p.capacity = capacity;
        p.free_head = 0;

        for (u64 i = 0; i < capacity; ++i) {
                u64* next_idx = (u64*)(p.base + i * block_size);
                *next_idx = (i + 1 < capacity) ? (i + 1) : POOL_NONE;
        }
        return p;
}

Pool pool_from_buffer(void* memory, u64 block_size, u64 capacity) {
        Pool p = {0};
        if (!memory || capacity == 0) return p;
        block_size = pool_round_block(block_size);
        p.base = (u8*)memory;
        p.block_size = block_size;
        p.capacity = capacity;
        p.free_head = 0;
        for (u64 i = 0; i < capacity; ++i) {
                u64* next_idx = (u64*)(p.base + i * block_size);
                *next_idx = (i + 1 < capacity) ? (i + 1) : POOL_NONE;
        }
        return p;
}

void pool_destroy(Pool* p) {
        if (!p || !p->base) return;
        MemRegion r = {
            .ptr = p->base,
            .size = p->block_size * p->capacity,
            .owns = 1};
#if MEMORY_USE_VM
#        if BASE_OS_WINDOWS
        VirtualFree(r.ptr, 0, MEM_RELEASE);
#        elif BASE_OS_LINUX || BASE_OS_MACOS || BASE_OS_FREEBSD ||  \
            BASE_OS_NETBSD || BASE_OS_OPENBSD || BASE_OS_ILLUMOS || \
            BASE_OS_UNIX
        munmap(r.ptr, (size_t)r.size);
#        else
        free(r.ptr);
#        endif
#else
        free(r.ptr);
#endif
        MemoryZeroStruct(p);
}

void* pool_alloc(Pool* p) {
        if (!p || p->free_head == POOL_NONE) return null;
        u64 idx = p->free_head;
        u8* block = p->base + idx * p->block_size;
        // cabeça aponta para o próximo
        u64 next = *(u64*)block;
        p->free_head = next;
        return (void*)block;
}

void pool_free(Pool* p, void* ptr) {
        Assert(p && ptr);
        u8* b = (u8*)ptr;
        Assert(
            b >= p->base &&
            b < p->base + p->block_size * p->capacity);
        Assert((((u64)(b - p->base)) % p->block_size) == 0);
        u64 idx = (u64)(b - p->base) / p->block_size;
        // coloca de volta na cabeça
        *(u64*)b = p->free_head;
        p->free_head = idx;
}
