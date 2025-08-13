#pragma once

#include "types.h"
#include "macros.h"

/*
 *
 * NOTE: Constants
 *
 * */

global const u8 u8_max = 0xff;
global const u16 u16_max = 0xffff;
global const u32 u32_max = 0xffffffff;
global const u64 u64_max = 0xffffffffffffffff;

global const i8 i8_max = 0x7f;
global const i16 i16_max = 0x7fff;
global const i32 i32_max = 0x7fffffff;
global const i64 i64_max = 0x7fffffffffffffff;

global const i8 i8_min = -0x7f;
global const i16 i16_min = -0x7fff;
global const i32 i32_min = -0x7fffffff;
global const i64 i64_min = -0x7fffffffffffffff;

global const f32 f32_machine_epsilon = 1.192092896e-07F;
global const f32 f32_pi = 3.14159265359F;
global const f32 f32_tau = 6.28318530718F;
global const f32 f32_golden_ratio = 1.61803398875F;
global const f32 f32_gold_small = 0.61803398875F;

global const f64 f64_machine_epsilon = 2.220446e-16;
global const f64 f64_pi = 3.14159265359;
global const f64 f64_tau = 6.28318530718;
global const f64 f64_golden_ratio = 1.61803398875;
global const f64 f64_gold_small = 0.61803398875;

/*
 *
 * NOTE: Float const functions
 *
 * */

static inline f32 f32_inf(void) {
        const u32 inf = 0x7f800000;
        union {
                f32 f;
                u32 u;
        } uni = {.u = inf};
        return uni.f;
}

static inline f32 f32_neg_inf(void) {
        const u32 neg_inf = 0xff800000;
        union {
                f32 f;
                u32 u;
        } uni = {.u = neg_inf};
        return uni.f;
}

static inline f64 f64_inf(void) {
        const u64 inf = 0x7ff0000000000000;
        union {
                f64 f;
                u64 u;
        } uni = {.u = inf};
        return uni.f;
}

static inline f64 f64_neg_inf(void) {
        const u64 neg_inf = 0xfff0000000000000;
        union {
                f64 f;
                u64 u;
        } uni = {.u = neg_inf};
        return uni.f;
}

