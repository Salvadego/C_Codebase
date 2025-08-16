#pragma once

/*
 *
 * NOTE: Float functions
 *
 * */

#include "macros.h"
#include "types.h"

function inline f32 f32_abs(f32 num) {
        return num < 0 ? -num : num;
}

function inline f64 f64_abs(f64 num) {
        return num < 0 ? -num : num;
}
