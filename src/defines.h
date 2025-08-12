#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "stddef.h"

#define global static
#define local static
#define function static

// Unsigned int types.
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Regular int types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Float types.
typedef float f32;
typedef double f64;

// Boolean types.
typedef i8 b8;
typedef i16 b16;

#define true 1
#define false 0

// Void type.
typedef void VoidFunc(void);

// Constants
global const u8 u8_max = 0xff;
global const u16 u16_max = 0xffff;
global const u32 u32_max = 0xffffffff;
global const u64 u64_max = 0xffffffffffffffff;

global const i8 i8_max = 0x7f;
global const i16 i16_max = 0x7fff;
global const i32 i32_max = 0x7fffffff;
global const i64 i64_max = 0x7fffffffffffffff;

global const u8 u8_min = 0;
global const u16 u16_min = 0;
global const u32 u32_min = 0;
global const u64 u64_min = 0;

global const i8 i8_min = -0x7f;
global const i16 i16_min = -0x7fff;
global const i32 i32_min = -0x7fffffff;
global const i64 i64_min = -0x7fffffffffffffff;

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
