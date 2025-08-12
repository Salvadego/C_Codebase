
#include "../src/defines.h"

#include <stdio.h>

void assert_unsigned(void) {
        Assert(sizeof(u8) == 1);
        Assert(sizeof(u16) == 2);
        Assert(sizeof(u32) == 4);
        Assert(sizeof(u64) == 8);
}

void assert_integer(void) {
        Assert(sizeof(i8) == 1);
        Assert(sizeof(i16) == 2);
        Assert(sizeof(i32) == 4);
        Assert(sizeof(i64) == 8);
}

void assert_sizes(void) {
        assert_unsigned();
        assert_integer();
}

void assert_defines(void) {
        int x = 5;
        int y = 10;

        Assert(Min(x, y) == 5);
        Assert(Max(x, y) == 10);

        Assert(Clamp(0, 7, 10) == 7);
        Assert(Clamp(0, -1, 10) == 0);
        Assert(Clamp(0, 11, 10) == 10);

        int arr[5];
        Assert(ArrayCount(arr) == 5);

        printf("defines.h macro tests passed\n");
}

int main(void) {
        assert_sizes();
        assert_defines();

        printf("types.h size tests passed\n");
        return 0;
}
