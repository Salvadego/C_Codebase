#pragma once

/*
 *
 * NOTE: Float functions
 *
 * */

function inline f32 f32_abs(f32 num) {
        const u32 mask = 0x7fffffff;
        union {
                f32 f;
                u32 u;
        } uni = {.f = num};
        uni.u &= mask;
        return uni.f;
}

function inline f64 f64_abs(f64 num) {
        const u64 mask = 0x7fffffffffffffff;
        union {
                f64 f;
                u64 u;
        } uni = {.f = num};
        uni.u &= mask;
        return uni.f;
}
