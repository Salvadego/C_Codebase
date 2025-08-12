#pragma once

#include "stdio.h"
#include "string.h"
#include "stddef.h"
#include "types.h"

#define null 0
#define u32_max 4294967295

#define Statement(S) \
        do {         \
                S    \
        } while (0)

#if defined(BASE_COMPILER_CLANG)
#        define FILE_NAME __FILE_NAME__
#else
#        define FILE_NAME __FILE__
#endif

#define flush fflush(stdout)
#define trace Statement(printf("%s:%d: Trace\n", FILE_NAME, __LINE__); flush;)
#define unreachable                                              \
        Statement(printf(                                        \
                      "How did we get here? In %s on line %d\n", \
                      FILE_NAME,                                 \
                      __LINE__);                                 \
                  flush;)

#if !defined(AssertBreak)
#        define AssertBreak() (*(int *)0 = 0)
#endif

#if ENABLE_ASSERT
#        define AssertFailed(expr, file, line)                \
                Statement(fprintf(                            \
                              stderr,                         \
                              "Assert failed: %s at %s:%d\n", \
                              expr,                           \
                              file,                           \
                              line);                          \
                          flush;                              \
                          AssertBreak();)

#        define Assert(cond)                                      \
                Statement(if (!(cond)) {                          \
                        AssertFailed(#cond, FILE_NAME, __LINE__); \
                })
#else
#        define Assert(cond) ((void)0)
#endif

#define Stringify(x) #x
#define Glue(x, y) x##y

#define ArrayCount(a) (sizeof(a) / sizeof(*(a)))

#define IntFromPtr(p) ((uintptr_t)(p))
#define PtrFromInt(i) ((void *)(uintptr_t)(i))

#define OffsetOfMember(T, m) offsetof(T, m)

#define Gigabytes(count) (u64)((count) * 1024 * 1024 * 1024)
#define Megabytes(count) (u64)((count) * 1024 * 1024)
#define Kilobytes(count) (u64)((count) * 1024)

#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))
#define ClampTop(a, b) Min(a, b)
#define ClampBot(a, b) Max(a, b)
#define ReverseClamp(a, x, b) (((x) < (a)) ? (b) : ((b) < (x)) ? (a) : (x))
#define Wrap(a, x, b) ReverseClamp(a, x, b)

#define MemoryZero(d, z) memset((d), 0, (z))
#define MemoryZeroStruct(d) MemoryZero((d), sizeof(*(d)))
#define MemoryZeroArray(d) MemoryZero((d), sizeof(d))
#define MemoryZeroTyped(d, t) MemoryZero((d), sizeof(*(d)) * (t))

#define MemoryMatch(a, b, z) (memcmp((a), (b), (z)) == 0)

#define MemoryCopy(d, s, z) memmove((d), (s), (z))
#define MemoryCopyStruct(d, s) \
        MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s))))
#define MemoryCopyArray(d, s) MemoryCopy((d), (s), Min(sizeof(s), sizeof(d)))
#define MemoryCopyTyped(d, s, t) \
        MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s))) * (t))

#define global static
#define local static
#define function static
