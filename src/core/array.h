#pragma once
#include "../base/base.h"
#include "memory.h"

#define DefineArrayType(T, name)                                     \
                                                                     \
        typedef struct {                                             \
                T *data;                                             \
                u64 count;                                           \
                u64 capacity;                                        \
                Arena *arena;                                        \
        } Glue(name, Array);                                         \
                                                                     \
        void Glue(name, ArrayInit)(                                  \
            Glue(name, Array) * a, Arena * arena) {                  \
                a->arena = arena;                                    \
                a->count = 0;                                        \
                a->capacity = 8;                                     \
                a->data = (T *)arena_push(                           \
                    a->arena, a->capacity * sizeof(T));              \
                Assert(a->data);                                     \
        }                                                            \
                                                                     \
        void Glue(name, ArrayPush)(Glue(name, Array) * a, T value) { \
                if (a->count >= a->capacity) {                       \
                        u64 new_cap =                                \
                            a->capacity ? a->capacity * 2 : 8;       \
                        T *new_data = (T *)arena_push(               \
                            a->arena, new_cap * sizeof(T));          \
                        Assert(new_data);                            \
                        if (a->data)                                 \
                                MemoryCopy(                          \
                                    new_data,                        \
                                    a->data,                         \
                                    a->count * sizeof(T));           \
                        a->data = new_data;                          \
                        a->capacity = new_cap;                       \
                }                                                    \
                a->data[a->count++] = value;                         \
        }                                                            \
                                                                     \
        T Glue(name, ArrayGet)(Glue(name, Array) * a, u64 index) {   \
                Assert(index < a->count);                            \
                return a->data[index];                               \
        }
