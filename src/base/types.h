
#pragma once

#include <stdint.h>

/*
 *
 * NOTE: Types Aliases
 *
 * */

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
